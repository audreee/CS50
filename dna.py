# implements a program that identifies a person based on their DNA short tandem repeats

import sys
import csv
import re

# checks usage
if len(sys.argv) != 3:
    print("enter csv file and data sequence")

# declares list of DNA STR sequences and list of max number of each STR's repeats
seq = []
data = []

# opens CSV and populates sequences list
with open(sys.argv[1]) as csvfile:
    csv_reader = csv.reader(csvfile)
    headings = next(csv_reader)
    for x in range(1, len(headings)):
        seq.append(headings[x])

# opens text file of a dna sequence
with open(sys.argv[2]) as dna_input:
    dna = dna_input.read()

    # looks at each STR-sequence
    for index in seq:

        # find matches between STR and full DNA sequence and saves starting index for each match
        matches = re.finditer(index, dna)
        match_positions = [int(match.start()) for match in matches]

        # stores number of consecutive matches and maximum number of consecutive repeats
        consecutive_matches = 1
        max_repeats = consecutive_matches

        for i in range(len(match_positions) - 1):
            if match_positions[i] + len(index) == match_positions[i + 1]:
                consecutive_matches += 1
                if max_repeats <= consecutive_matches:
                    max_repeats = consecutive_matches

            else:
                consecutive_matches = 1
                if max_repeats <= consecutive_matches:
                    max_repeats = consecutive_matches

        # adds number of max repeats to list
        data.append(str(max_repeats))

# opens database csv and prints name of person with matching dna
with open(sys.argv[1]) as csvfile:
    same = False
    csv_reader = csv.reader(csvfile)
    for row in csv_reader:
        r = row[1:]
        if r == data:
            same = True
            print(row[0])
    if same is False:
        print("No match")
