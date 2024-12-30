import pandas as pd

def calculate_throughput(file):
    data = pd.read_csv(file, skiprows=1)
    
    data.columns = [
        "start", "end", "CellId", "IMSI", "RNTI", "LCID",
        "nTxPDUs", "TxBytes", "nRxPDUs", "RxBytes", "delay", "stdDev",
        "minDelay", "maxDelay", "PduSize", "stdDevPdu", "minPdu", "maxPdu"
    ]
    
    bytes = data.groupby("IMSI")["TxBytes"].sum()

    time = data["end"].max() - data["start"].min()

    megabitsPerSecond = (bytes * 8) / (time * 1000000)

    for imsi, throughput in megabitsPerSecond.items():
        print(f"IMSI {int(imsi)}: {throughput:.2f} Мбит/с")

dlFile = "DlRlcStats.txt"
print("Throughput (DL):")
calculate_throughput(dlFile)

ulFile = "UlRlcStats.txt"
print("Throughput (UL):")
calculate_throughput(ulFile)