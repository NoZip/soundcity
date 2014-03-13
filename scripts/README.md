Scripts
=======

Extraction de la MSD
--------------------

Pour extraire La MSD sous forme de base de données SQLite3, il suffit d'indiquer
au script la localisation du dossier data/ de la MSD:

    python3 dump_msd.py /MillionSongSubset/data/ test.db

Cette opération peut prendre du temps. Si vous relancez le script n'oubliez pas
de supprimer le fichier «.db».
