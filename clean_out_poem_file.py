filename = "poem.txt" 

chapter_symbols = ["I\n", "V\n", "X\n", "L\n", "C\n"]

with open(filename, "r", encoding="UTF-8") as f_r, open("clean_" + filename, "w", encoding="UTF-8") as f_w:
    for line in f_r:
        if (not line.isspace()) and (". . . ." not in line) and all([elem not in line for elem in chapter_symbols]):
            f_w.write(line)