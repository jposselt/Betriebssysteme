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

# txt Datei?
istxt () {
    if [ "$(echo "$1" | cut -d'.' -f2)" == txt ]
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

TYPESTRING="Dateityp: "
LINKSTRING="Symbolischer Link: "
CALLERSTRING="Aufrufer ist Besitzer: "

for FILE in $@
do
    echo "*-------------------------------*"

    if fileexists "$FILE"
    then
	echo "Datei $FILE existiert"
	
	# Ausgabe Dateityp
	if getfiletype "$FILE"
	then
	    echo $TYPESTRING $filetype
	else
	    echo $TYPESTRING "unbestimmt"
	fi
	
	# Ausgabe Symlink
	if symlink "$FILE"
	then
	    echo $LINKSTRING "Ja"
	else
	    echo $LINKSTRING "Nein"
	fi
	
	# Ausgabe Caller=Owner
	if callerisowner "$FILE"
	then
	    echo $CALLERSTRING "Ja"
	else
	    echo $CALLERSTRING "Nein"
	fi

	# Ausgabe Besitzer
	echo "Besitzer:" $(ls -ld $FILE | cut -d" " -f3)

	# Prüfe auf txt
	if istxt "$FILE"
	then
	    echo "Datei anzeigen?"
	    select CHOICE in Ja Nein
	    do
		if [ "$CHOICE" == Ja ]
		then
		    less "$FILE"
		    break
		else
		    break
		fi	    
	    done
	fi
	
    else
	echo "Datei $FILE existiert nicht."
    fi
done

echo "*-------------------------------*"

exit 0
