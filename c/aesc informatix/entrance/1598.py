string = input()
string = string.strip()
string = list(string)
for idx, x in enumerate(string):
    while string[idx-1] == " " and string[idx] == " ":
        string.pop(idx)

string = ''.join(string)
print(string)