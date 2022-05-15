from PyQt6 import QtCore


def create_dir(path, name):
    curr_dir = QtCore.QDir(path)
    if not curr_dir.exists(name):
        if not curr_dir.mkdir(name):
            raise RuntimeError("Cannot create directory")
        print("Directory created successfully")
    else:
        print("Directory already exists")


def remove_dir(path, name):
    curr_dir = QtCore.QDir(path)
    if curr_dir.exists(name):
        if not curr_dir.rmdir(name):
            raise RuntimeError("Cannot remove directory")
        print("Directory removed successfully")
    else:
        print("Directory does not exist")


def rename_dir(path, old_name, new_name):
    curr_dir = QtCore.QDir(path)
    if curr_dir.exists(old_name):
        old_path_absolute = curr_dir.absolutePath() + "/" + old_name
        # check if it exists
        if not QtCore.QFileInfo(old_path_absolute).isDir():
            raise RuntimeError("Dir does not exist")
        new_path_absolute = curr_dir.absolutePath() + "/" + new_name
        # check if it exists
        if QtCore.QFileInfo(new_path_absolute).isDir():
            raise RuntimeError("New name is already in use")
        if not curr_dir.rename(old_name, new_name):
            raise RuntimeError("Cannot rename dir")
        print("Dir renamed successfully")
    else:
        print("Directory does not exist")


def create_file(path, name, content):
    curr_dir = QtCore.QDir(path)
    if not curr_dir.exists(name):
        file = QtCore.QFile(path + "/" + name)
        if not file.open(
            QtCore.QIODevice.OpenModeFlag.WriteOnly | QtCore.QIODevice.OpenModeFlag.Text
        ):
            raise RuntimeError("Cannot create file")
        text_stream = QtCore.QTextStream(file)
        for i in range(len(content)):
            text_stream << content[i] + "\n"
        file.close()
        print("File created successfully")

    else:
        print("File already exists")


def remove_file(path, name):
    curr_dir = QtCore.QDir(path)
    if curr_dir.exists(name):
        if not curr_dir.remove(name):
            raise RuntimeError("Cannot remove file")
        print("File removed successfully")
    else:
        print("File does not exist")


def main():
    path = QtCore.QDir.tempPath()
    dir_name = "test_dir"
    new_dir_name = "new_test_dir"
    file_name = "test_file_1"
    file_name_2 = "test_file_2"
    content = ["Hello", "World"]

    try:
        create_dir(path, dir_name)
        rename_dir(path, dir_name, new_dir_name)

        new_path = path + QtCore.QDir.separator() + new_dir_name

        create_file(new_path, file_name, content)
        create_file(new_path, file_name_2, content)

        remove_file(new_path, file_name)
        remove_file(new_path, file_name_2)

        remove_dir(path, new_dir_name)
    except RuntimeError as e:
        print(e)


if __name__ == "__main__":
    main()
