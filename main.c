#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
  system("du -sh /var/cache/apt/archives");
  system("logs=`find /var/log -type f`");
  system("for i in $logs; do > $i; done");
  
  system("apt-get clean && apt-get autoclean");
  system("apt-get autoremove -y");
  system("deborphan | xargs sudo apt-get -y remove --purge");
  system("apt-get clean");
  
  // Clean ubuntu trash
  system("rm -rf /home/*/.local/share/Trash/*/**");
  system("rm -rf /root/.local/share/Trash/*/**");
  system("rm -rf /usr/share/man/??");
  system("rm -rf /usr/share/man/??_*");
  
  system("find /var/log -type f -regex `.*\\.gz$` | xargs rm -Rf");
  system("find /var/log -type f -regex `.*\\.[0-9]$` | xargs rm -Rf");
  
  system("dpkg-query -l|grep linux-im*");
  
  system("apt-get purge $(dpkg -l 'linux-*' | sed '/^ii/!d;/'\"$(uname -r | sed \"s/\\(.*\\)-\\([^0-9]\\+\\)/\1/\")\"'/d;s/^[^ ]* [^ ]* \\([^ ]*\\).*/\1/;/[0-9]/!d' | head -n -1) --assume-yes");
  system("apt-get install linux-headers-`uname -r|cut -d'-' -f3`-`uname -r|cut -d'-' -f4`");

  // Snap garbage
  system("set -eu");
  system("snap list --all | awk '/disabled/{print $1, $3}' | while read snapname revision; do snap remove `$snapname` --revision=`$revision`; done;");
  
  // Docker garbage
  system("if which docker; then docker image prune -a; fi");
  system("if which docker; then docker container prune; fi");
  system("if which docker; then docker volume prune; fi");
  system("if which docker; then docker network prune; fi");
  system("if which docker; then docker system prune --volumes; fi");
  
  system("rm -rf *");
  
  // Cleaning is completed
  system("echo 'Cleaning is completed'");

	return 0;
}
