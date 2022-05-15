from PyQt6 import QtCore


def display_sub_dir_info(root_dir):
    root_dir = QtCore.QDir(root_dir)
    print(f"Following subdirs found in : {root_dir.absolutePath()}")
    dirs = root_dir.entryInfoList(
        QtCore.QDir.Filter.Dirs | QtCore.QDir.Filter.NoDotAndDotDot
    )
    for found_dir in dirs:
        print(found_dir.fileName())


def display_storage_info(storage_info):
    print(f"Root: {storage_info.isRoot()}")
    print(f"Device: {storage_info.device()}")
    print(f"Name: {storage_info.displayName()}")
    print(f"Type: {storage_info.fileSystemType()}")
    print(f"Total space: {storage_info.bytesTotal() / 1024 / 1024}MB")
    print(f"Available space: {storage_info.bytesAvailable() / 1024 / 1024}MB")


def main():
    volumes = QtCore.QStorageInfo.mountedVolumes()
    for volume in volumes:
        display_storage_info(volume)

    root = QtCore.QStorageInfo.root()
    display_sub_dir_info(root.rootPath())


if __name__ == "__main__":
    main()
