import requests
import matplotlib.pyplot as plt

def get_gold_data(start,end):
    url=f"http://api.nbp.pl/api/cenyzlota/{start}/{end}"
    response=requests.get(url)
    data=response.json()
    return data

def make_plot():
    plt.figure(figsize=(10,6))
    data_2021=get_gold_data("2021-01-01","2021-12-31")
    data_2022=get_gold_data("2022-01-01","2022-12-31")
    data_2023=get_gold_data("2023-01-01","2023-11-30")
    miesiace_2021={}
    miesiace_2022={}
    miesiace_2023={}
    for i in data_2021:
        data=i["data"][5:7]
        if data in miesiace_2021:
            miesiace_2021[data]+=i["cena"]
        else:
            miesiace_2021[data]=i["cena"]
    for i in data_2022:
        data=i["data"][5:7]
        if data in miesiace_2022:
            miesiace_2022[data]+=i["cena"]
        else:
            miesiace_2022[data]=i["cena"]
    for i in data_2023:
        data=i["data"][5:7]
        if data in miesiace_2023:
            miesiace_2023[data]+=i["cena"]
        else:
            miesiace_2023[data]=i["cena"]
    srednie_2021=[round(miesiace_2021[i]/30,2) for i in miesiace_2021]
    srednie_2022=[round(miesiace_2022[i]/30,2) for i in miesiace_2022]
    srednie_2023=[round(miesiace_2023[i]/30,2) for i in miesiace_2023]
    #w 2023 nie ma danych na grudzien wiec daje przewidywane
    przewidywania_2023=[]
    for i in range(len(srednie_2021)):
        przewidywania_2023.append(round(srednie_2022[i]+0.05*srednie_2022[i]))
    srednie_2023.append(srednie_2022[11]+srednie_2022[11]*0.05)
    miesiace=[x for x in miesiace_2021]
    plt.plot(miesiace,srednie_2021,label="Ceny w 2021",color="blue")
    plt.plot(miesiace,srednie_2022, label="Ceny w 2022", color="red")
    plt.plot(miesiace,przewidywania_2023, label="Ceny w 2023 (p)", color="green")
    plt.plot(miesiace,srednie_2023, label="Ceny w 2023", color="purple")
    plt.xlabel("Miesiąc")
    plt.ylabel("Cena")
    plt.title("Ceny złota w latach 2021, 2022 i 2023")
    plt.legend()
    plt.show()

make_plot()



