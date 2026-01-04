!#/bin/sh
# раскладка
setxkbmap -layout "us,ru" -option "grp:shifts_toggle" &

# отклик клавы
xset r rate 240 30 &

# мониторы
sh /home/uwuty/.screenlayout/skreen.sh

# обои
#feh --bg-scale /home/uwuty/data/normalniy_foto/wallpaper/anime/wallpaperflare.com_wallpaper.jpg &
feh --bg-fill ~/data/normalniy_foto/wallpaper/anime/wallpaperflare.com_wallpaper.jpg  ~/data/normalniy_foto/wallpaper/anime/devushka_siluet_planeta_1067694_1280x1024.jpg

# автозаупуск приложений
firefox &
throne &

# статус бар
slstatus &

# polkit
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &

# для буфера обмена
clipmenud &

# блок мониторы для тышки
xpointerbarrier 0 0 0 0

# прозрачность
picom &

# уведомления
dunst &

exec dusk

#[Desktop Entry]
#Encoding=UTF-8
#Name=dusk
#Comment=dusk - a dwm fork
#Exec=/home/uwuty/.startdusk
#Icon=dusk
#Type=XSession
