#!/bin/bash

# Prüft, ob Datei existiert
fileexists () {
    if [ -e "$1" ]
    then
	return 0
    else
	return 1
    fi
}

# Dateityp
getfiletype () {
    if [ -f "$1" ] # reguläre Datei?
    then
	export filetype="reguläre Datei"
	return 0
    elif [ -d "$1" ] # verzeichnis?
    then
	export filetype="Verzeichnis"
	return 0
    else
	return 1
    fi
}

# Symbolischer Link?
symlink () {
    if [ -h "$1" ]
    then
	return 0
    else
	return 1
    fi
}

# Aufrufer ist Besitzer?
callerisowner () {
    if [ -O "$1" ]
    then
	return 0
    else
	return 1
    fi
}


# Parameter prüfen
if [ -z "$1" ]
then
    echo "Usage: $0 pfad"
    exit 1
fi

typestring="Dateityp: "
linkstring="Symbolischer Link: "
callerstring="Aufrufer ist Besitzer: "

echo "*-------------------------------*"

if fileexists "$1"
then
    echo "Datei $1 existiert"
    
    # Ausgabe Dateityp
    if getfiletype "$1"
    then
	echo $typestring $filetype
    else
	echo $typestring "unbestimmt"
    fi

    # Ausgabe Symlink
    if symlink "$1"
    then
	echo $linkstring "Ja"
    else
	echo $linkstring "Nein"
    fi

    # Ausgabe Caller=Owner
    if callerisowner "$1"
    then
	echo $callerstring "Ja"
    else
	echo $callerstring "Nein"
    fi

    # Ausgabe Besitzer
    echo "Besitzer:" $(ls -ld $1 | cut -d" " -f3)
	   
else
    echo "Datei $1 existiert nicht."
fi

echo "*-------------------------------*"

exit 0
