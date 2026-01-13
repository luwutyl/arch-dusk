!#/bin/sh
# раскладка
setxkbmap -layout "us,ru" -option "grp:shifts_toggle" &

# отклик клавы
xset r rate 240 30 &

# мониторы
sh /home/uwuty/.screenlayout/skreen.sh

# обои
#feh --bg-scale /home/uwuty/data/normalniy_foto/wallpaper/anime/wallpaperflare.com_wallpaper.jpg &
feh --no-fehbg --bg-fill /home/uwuty/data/normalniy_foto/wallpaper/abstract/purple-electric-bolts-aesthetic-desktop-wallpaper-4k.jpg /home/uwuty/data/normalniy_foto/wallpaper/abstract/704e41f9a0b5ef365759e52bd06c34ba.jpg

# автозаупуск приложений
firefox &
throne &
Telegram -startintray &

# статус бар
slstatus &

# polkit
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &

# для буфера обмена
clipmenud &

# прозрачность
picom &

# уведомления
dunst &

# отключиь выключение экрана
xset s off -dpms &

exec dusk

#[Desktop Entry]
#Encoding=UTF-8
#Name=dusk
#Comment=dusk - a dwm fork
#Exec=/home/uwuty/.startdusk
#Icon=dusk
#Type=XSession
