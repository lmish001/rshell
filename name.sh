#!/bin/sh

#Responsible for getting the best available username and machinename(hostname)
#Username and hostname are flipped depending on the system you are on

USERNAME=$(id -un)
HOSTNAME=$(hostname -f)
HOSTNAME=${HOSTNAME%%.*}
HOSTNAME=${HOSTNAME%%-*}

BLUE='\033[0;34m'
GREEN='\033[0;32m'
REG='\033[0m'

if [ "$USERNAME" = "ubuntu" ]; then
     printf "${BLUE}${HOSTNAME}${REG}@${GREEN}${USERNAME}${REG}$ "
else
     printf "${BLUE}${USERNAME}${REG}@${GREEN}${HOSTNAME}${REG}$ "
fi