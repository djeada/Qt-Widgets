def dict_to_json(root, spaces=4):
    content = list()

    def value_to_json_format(value):
        if isinstance(value, str):
            return '"' + value + '"'
        elif isinstance(value, list):
            return "[" + ", ".join(value_to_json_format(v) for v in value) + "]"
        return str(value)

    def remove_trailing_commas():
        if content[-1][-1] == ",":
            content[-1] = content[-1][:-1]

    def _dict_to_json_inner(root, level=1):
        for key, value in root.items():
            if isinstance(value, dict):
                content.append("\n" + " " * level * spaces + '"' + key + '": {')
                _dict_to_json_inner(value, level + 1)
                remove_trailing_commas()
                content.append("\n" + " " * level * spaces + "},")
            else:
                content.append(
                    f"{' ' * level * spaces}\"{key}\": {value_to_json_format(value)},"
                )
        remove_trailing_commas()

    _dict_to_json_inner(root)
    return ["{"] + content + ["}"]
