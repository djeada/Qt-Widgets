from PyQt6 import QtCore

def display_sub_dir_info(root_dir):
    print(f"Following subdirs found in : {root_dir.absolutePath()}")
    dirs = root_dir.entryInfoList(QtCore.QDir.Filter.Dirs | QtCore.QDir.Filter.NoDotAndDotDot)
    for found_dir in dirs:
        print(found_dir.fileName())

def display_child_files_info(root_dir):
    print(f"Following files found in : {root_dir.absolutePath()}")
    files = root_dir.entryInfoList(QtCore.QDir.Filter.Files)
    for file in files:
        print(f"Name: {file.fileName()}")
        print(f"Size: {file.size() / 1024}KB")
        print(f"Created: {file.birthTime().toString()}")
        print(f"Modified: {file.lastModified().toString()}")


def display_file_info(path):
    root_dir = QtCore.QDir(path)
    display_sub_dir_info(root_dir)
    display_child_files_info(root_dir)


def main():
    # display_file_info(QtCore.QDir.tempPath())
    display_file_info(QtCore.QDir.homePath())


if __name__ == '__main__':
    main()
