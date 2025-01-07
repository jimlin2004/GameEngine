#include "Platform/Windows/WindowsApi.h"

#include <cstring>

#include <string>
#if USE_WINDOWS

std::string GameEngineEditor::WindowsApi::openProjectFile(HWND parentID)
{
    // CHAR filePathBuffer[512] = {0};
    // OPENFILENAME ofn;
    // ZeroMemory(&ofn, sizeof(OPENFILENAME));
    // ofn.lStructSize = sizeof(OPENFILENAME);
    // ofn.hwndOwner = parentID;
    // ofn.lpstrFilter = "project file(*.gproject)\0*.gproject\0";
    // ofn.nFilterIndex = 1;
    // ofn.lpstrFile = filePathBuffer;
    // ofn.lpstrFile[0] = '\0';
    // ofn.nMaxFile = sizeof(filePathBuffer);
    // ofn.lpstrInitialDir = NULL;
    // ofn.lpstrTitle = "Open Project\0";
    // ofn.nMaxFileTitle = strlen("Open Project\0");
    // ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    // if (GetOpenFileNameA(&ofn))
    // {
    //     return ofn.lpstrFile;
    // }
    // return std::string();

    // 以下是比較新的對話窗API
    // 初始化COM庫
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr))
    {
        return std::string();
    }

    // 創建FileOpenDialog介面
    IFileOpenDialog* pFileOpen = nullptr;
    hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_IFileOpenDialog, (void**)&pFileOpen);
    if (SUCCEEDED(hr))
    {
        // 設置檔案篩選條件
        COMDLG_FILTERSPEC fileTypes[] =
        {
            {L"Project Files (*.gproject)", L"*.gproject"}
        };
        pFileOpen->SetFileTypes(1, fileTypes); // 1表示篩選條件的數量
        pFileOpen->SetFileTypeIndex(1);       // 預設選中的篩選條件
        pFileOpen->SetTitle(L"Open Project"); // 對話框標題

        // 顯示對話框
        hr = pFileOpen->Show(parentID);
        if (SUCCEEDED(hr))
        {
            // 獲取用戶選擇的檔案
            IShellItem* pItem = nullptr;
            hr = pFileOpen->GetResult(&pItem);
            if (SUCCEEDED(hr))
            {
                PWSTR filePath = nullptr;
                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

                // 將結果轉換為 std::string
                if (SUCCEEDED(hr))
                {
                    char filePathBuffer[MAX_PATH];
                    WideCharToMultiByte(CP_ACP, 0, filePath, -1, filePathBuffer, MAX_PATH, nullptr, nullptr);
                    CoTaskMemFree(filePath); // 釋放COM內存
                    pItem->Release();
                    pFileOpen->Release();
                    CoUninitialize();
                    return std::string(filePathBuffer);
                }
                pItem->Release();
            }
        }
        pFileOpen->Release();
    }

    // 清理COM
    CoUninitialize();
    return std::string();
}

std::string GameEngineEditor::WindowsApi::openFile(HWND parentID, const char* filter)
{
    CHAR filePathBuffer[512] = {0};
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = parentID;
    ofn.lpstrFilter = filter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = filePathBuffer;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(filePathBuffer);
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = "Open File\0";
    ofn.nMaxFileTitle = strlen("Open File\0");
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    if (GetOpenFileNameA(&ofn))
    {
        return ofn.lpstrFile;
    }
    return std::string();
}

#endif