#!/bin/bash

# Shell Script zum 'löschen' von Dateien. Dateien werden zunächst in ein
# Papierkorbverzeichnis verschoben und nach Zeitstempel und PID benannt.

TRASHDIR="$HOME/.trashBin"
TRASHLOG="$TRASHDIR/.dir"

#echo $(date '+%y%m%d%H%M%S')

deleteFile() {
    if [ -e "$1" ]
    then
	# Dateihandle anlegen
	HANDLE=$(date '+%y%m%d%H%M%S')_$BASHPID.dat
	
	# Datei verschieben
	mv "$1" "$TRASHDIR/$HANDLE" 2>/dev/null
	if [ "$?" -eq "0" ]
	then	
		# Eintrag zur Logdatei hinzufügen
		echo $HANDLE! $(realpath -s "$1") >> "$TRASHLOG"

		# Ausgabe für Benutzer
		echo $(realpath -s "$1"): "$HANDLE"
	else 
	echo Fehler beim Löschen von "$1"
	fi
    else
	echo "$1 existiert nicht"
    fi
}

# Parameter prüfen
if [ -z "$1" ]
then
    echo "Usage: $0 [FILE]..."
    exit 1
fi

# Erzeuge Papierkorb, falls nicht vorhanden
if [ ! -e "$TRASHDIR" ]
then
    mkdir "$TRASHDIR"
fi

# Erzeuge Log-Datei, falls nicht vorhanden
if [ ! -e "$TRASHLOG" ]
then
    touch "$TRASHLOG"
fi

# Iteration über Parameterliste
for FILE in "$@"
do
    # Aufruf Funktion in Subshell
    (deleteFile "$FILE")
done
