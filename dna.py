import cs50 as c
import sys as s
import csv


def main():
    final_max = []
    if len(s.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")  # prints text if usage is incorrect
        s.exit(1)
    with open(s.argv[1], "r") as data:
        dict_list = list(csv.reader(data))  # reads the data
    # print(dict_list)
    sample = open(s.argv[2], "r")
    dna = sample.read()
    dna = str(dna)
    for strands in dict_list[0]:
        if strands == 'name':  # skips the first index
            continue
        max_value = []
        for i in range(len(dna) - (len(strands))):  # repeats for the amount of times
            dna_data = []
            dna_str = []
            for j in range(len(strands)):
                # print(j)
                dna_data.append(dna[i + j])
                # print(dna_data)
            dna_str = "".join(dna_data)  # makes a dna structure 
            if dna_str == strands:  # if that strand == to the thing we are looking for
                x = 1
                times_occured = 1
                starting_index = i

                while x == 1: 
                    dna_str1 = []
                    dna_data1 = []
                    starting_index = starting_index + len(strands)
                    for p in range(len(strands)):
                        if starting_index + p <= (len(dna) - 1):  # makes sure it doesn't overstep bound
                            # max_value.append(times_occured)
                            # continue
                            dna_data1.append(dna[starting_index + p])

                    dna_str1 = "".join(dna_data1)
                    if dna_str1 == strands:
                        times_occured = times_occured + 1
                    else:
                        max_value.append(times_occured)
                        x = 0
        if len(max_value) != 0:  # checks if len is max
            final_max.append(str(max(max_value)))  # then appends to the master list
    for rows in range(len(dict_list)):
        if rows == 0:
            continue
        numbers_need = []
        for i in range(len(dict_list[rows])):
            if i == 0:
                continue
            numbers_need.append(dict_list[rows][i])
        if numbers_need == final_max:
            print(dict_list[rows][0])  # looks through all rows for a matching list
            s.exit(0)
    print("No match")


main()