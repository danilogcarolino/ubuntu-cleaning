#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc)
{
  system("du -sh /var/cache/apt/archives");
  system("logs=`find /var/log -type f`");
  system("for i in $logs; do > $i; done");

  // Clean apt garbage
  system("apt clean && apt autoclean");
  system("apt full-upgrade -y");
  system("apt autoremove -y");
  system("deborphan | xargs sudo apt-get -y remove --purge");
  system("apt clean");

  // Clean ubuntu trash
  system("rm -rf /home/*/.local/share/Trash/*/**");
  system("rm -rf /root/.local/share/Trash/*/**");
  system("rm -rf /usr/share/man/??");
  system("rm -rf /usr/share/man/??_*");

  system('find /var/log -type f -regex ".*\.gz$" | xargs rm -Rf');
  system('find /var/log -type f -regex ".*\.[0-9]$" | xargs rm -Rf');

  // Snap garbage
  system("set -eu");
  system("snap list --all | awk '/disabled/{print $1, $3}' | while read snapname revision; do snap remove \"$snapname\" --revision=\"$revision\"; done;");

  // Cleaning is completed
  system("echo 'Cleaning is completed.'");

  return 0;
}
