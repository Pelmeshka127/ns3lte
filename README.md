# ns3lte

Здесь содержится lte сценарий с одной базовой станцией и двумя абонентами.
По выводу ключевых характеристик считается throughput в DL и UL для каждого пользователя.

Для запуска simplelte.cc нужно поместить установить симулятор ns3 и поместить файл в директорию scratch
```
./ns3 run scratch/simplelte.cc
```

Для вывода характеристик с Rlc уровня нужна библиотека pandas. Убедитесь, что у вас в директории присутствуют файлы DlRlcStats.txt и UlRlcStats.txt

```
python3 throughput.py
```

Или создайте виртуальное окружение
```
python3 -m env myenv
source myenv/bin/activate
pip install pandas
python3 throughput.py
```