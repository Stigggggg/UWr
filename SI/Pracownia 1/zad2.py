# zadanie zostało rozwiązane za pomocą dynamicznego programowania
# zgodnie z treścią zadania, szukamy najbardziej optymalnego słowa pod względem kwadratu długości
# w tablicy przechowujemy indeksy początku kolejnych słów, które odtwarzamy od tyłu, linia po linii

import gzip

def load_words(file):
    with gzip.open(file, 'rt', encoding='utf-8') as f:
        return set(line.strip() for line in f)

def process_text(text, words):
    dp = [-1] * (len(text) + 1)
    prev = [-1] * (len(text) + 1)
    dp[0] = 0
    for i in range(1, len(text) + 1):
        for j in range(max(0, i - 32), i):
            word = text[j:i]
            if word in words:
                score = dp[j] + len(word) ** 2
                if score > dp[i]:
                    dp[i] = score
                    prev[i] = j
    result = []
    index = len(text)
    while index > 0:
        prev_index = prev[index]
        result.append(text[prev_index:index])
        index = prev_index
    return ' '.join(result[::-1])
    
words = load_words('zad2_words.txt.gz')
with open('zad2_input.txt', 'r', encoding='utf-8') as fin, open('zad2_output.txt', 'w', encoding='utf-8') as fout:
    for line in fin:
        line = line.strip()
        fout.write(process_text(line, words) + '\n')