Scripts
=======

Extraction de la MSD
--------------------

Pour extraire La MSD sous forme de base de données SQLite3, il suffit d'indiquer
au script la localisation du dossier data/ de la MSD et le nom souhaité pour la
database (".db" y sera ajouté automatiquement):

    python3 dump_msd.py /MillionSongSubset/data/ test

Cette opération peut prendre du temps. Si vous relancez le script n'oubliez pas
de supprimer le fichier «.db».
