# WeatherStation
Погодная станция на аппаратной платформе Arduino с подключенными к ней датчиками для измерения температуры, влажности и атмосферного давления.
### Задача.
Необходимо обеспечить хранение получаемых значений в БД для возможности последующей их обработки.
Планируется реализовать следующие возможности обработки:
1. Получение последних данных о погоде через Телеграм бота по запросу.
2. Периодические автоматические уведомления о текущей погоде в Телеграм бота.
3. Прогнозирование изменения погоды на ближайшие сутки погоды на основе барометрической тенденции (для точности прогнозирования и обработки данных можно использовать различные сторонние сервисы, такие как OpenWeatherMap API, Weather Underground и т.д.).
4. Уведомления в Телеграм бота о резком ухудшении погоды в ближайшие часы.
5. Расчет ощущаемой температуры.

### Инструменты для реализации проекта:
1. Аппаратная платформа Arduino (Arduino Uno + Ethernet shield W5100) с датчиками для измерения температуры (DS18B20), влажности (DHT21) и атмосферного давления (BMP180).
2. Интегрированная среда разработки Arduino IDE.
3. Cкриптовый язык PHP для написания вкрипта записи в БД.
4. База данных MariaDB для хранения данных.
6. Язык программирования Python (+ интегрированная среда разработки PyCharm)  для написания скриптов обработки данных и для реализации Telegram бота.
7. Библиотеки для работы с Аrduino, БД MariaDB и Telegram API в Python.
8. Виртуальный сервер (ОС Debian) со статическим IP-адресом.
9. Среда визуализации данных (Grafana или Zabbix).
10. Система контроля версий Git.

### На текущий моммент реализовано:
1. Подключены датчики температуры и влажности.
2. Написан скетч Ардуино для получения данных с датчиков.
3. Расчет ощущаемой температуры.
4. Реализован вывод значений температуры, относительной влажности и ощущаемой температуры чрезез web-сервер Ethernet шилда.
5. Сбор информации о температцре и влажности в Zabbix путем парсинга web-страницы с выводом информации.
6. Периодические автоматические уведомления о текущей погоде в Телеграм бота средствами Zabbix.
