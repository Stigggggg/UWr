import re

def is_palindrom(text):
    new_text=re.sub("[^A-Za-z]", "", text.lower())
    return new_text == new_text[::-1]

print(is_palindrom("oko"))
print(is_palindrom("Kobyła ma mały bok."))
print(is_palindrom("Eine güldne, gute Tugend: Lüge nie!"))
print(is_palindrom("Míč omočím."))
