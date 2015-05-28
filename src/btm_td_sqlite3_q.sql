DROP TABLE IF EXISTS songinfo;
CREATE TABLE IF NOT EXISTS songinfo (
	id INTEGER PRIMARY KEY AUTOINCREMENT,
    filepath TEXT,
    filename TEXT,
    songname TEXT,
    songgroup TEXT,
    composer TEXT,
    genre TEXT,
    subgenre TEXT,
    num_tracks INT,
    instrument_names TEXT,
    CONSTRAINT file UNIQUE (
        filepath,
        filename
    )
);

INSERT INTO songinfo (filepath, filename, songname, songgroup, composer, genre, subgenre, num_tracks, instrument_names)
VALUES (':filepath', ':filename', ':songname', ':songgroup', ':composer', ':genre', ':subgenre', ':num_tracks', ':instrument_names');

UPDATE songinfo 
   SET songname = ':songname', 
	   songgroup = '?:songgroup', 
	   composer = ':composer', 
	   genre = ':genre', 
	   subgenre = ':subgenre', 
	   num_tracks = ':num_tracks', 
	   instrument_names = ':instrument_names'
 WHERE id = '?10' OR (filepath = ':filepath' AND filename = ':filename');
 
 1	./assets/midi/classical/Brahms	hungdan5.mid	Hungarian Dance No.5 Solo Piano	Hungarian Dances	Johannes Brahms	Classical	Dance	2	