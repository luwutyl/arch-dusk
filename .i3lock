#!/bin/bash

# Путь к временному файлу скриншота
IMAGE=/tmp/screen_lock.png

# 1. Делаем скриншот через Flameshot
# -f (full) — полный экран, -p — путь сохранения
#flameshot full -p $IMAGE
scrot $IMAGE

# 2. Обработка изображения через ImageMagick (convert)
# -blur 0x8: 0 — радиус, 8 — сигма (интенсивность размытия)
convert $IMAGE -blur 0x8 $IMAGE

# 3. Добавляем иконку замка в центр (опционально)
# Если у вас есть иконка lock.png, раскомментируйте строку ниже:
# convert $IMAGE /path/to/icon.png -gravity center -composite $IMAGE

# 4. Запуск i3lock с полученным изображением
# -i — путь к картинке, -n — не закрывать процесс сразу (полезно для xss-lock)
#i3lock -i $IMAGE

# i3lock-color сам рисует индикатор и раскладку динамически
i3lock -i $IMAGE --blur 8 --keylayout 1 --layout-color ffffffff --layout-font AdwaitaMono Nerd Font --time-color ffffffff --time-font AdwaitaMono Nerd Font --date-color ffffffff
# 5. Удаляем временный файл после разблокировки
rm $IMAGE
