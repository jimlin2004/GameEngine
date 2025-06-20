import os
import argparse


if (__name__ == "__main__"):
    parser = argparse.ArgumentParser()
    parser.add_argument("--project_name", type=str)
    parser.add_argument("--project_root", type=str)
    
    args = parser.parse_args()
    
    print("=======================================")
    print(f"Project name: {args.project_name}")
    print(f"Project path: {args.project_root}")
    print("=======================================")