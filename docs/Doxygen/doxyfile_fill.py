def read_file(filename):
    with open(filename, 'r') as file:
        return file.read()

def write_file(filename, content):
    with open(filename, 'w') as file:
        file.write(content)

def read_and_replace(filename, string, new_string):
    write_file(filename, read_file(filename).replace(string, new_string))
    print('Wrote `' + new_string + '` instead of `' + string + '` in `' +  filename + '`')
    
read_and_replace("Doxyfile.in", "@CMAKE_CURRENT_SOURCE_DIR@", "./docs")