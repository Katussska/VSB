# Hudební Katalog s SQL Databází

---

## Jendotlivé tabulky:

### Artists (Umělci)

- Sloupce: ArtistID (PK), Name, Biography, GenreID (FK)

### Genres (Žánry)

- Sloupce: GenreID (PK), Name, Description

### Songs (Písně)

- Sloupce: SongID (PK), SongName, ArtistID (FK), GenreID (FK), Lyrics, Tempo, ReleaseDate, Rating

### Users (Uživatelé)

- Sloupce: UserID (PK), Username, Password, Email

### Comments (Komentáře)

- Sloupce: CommentID (PK), UserID (FK), SongID (FK), CommentText, CommentDate

### Ratings (Hodnocení)

- Sloupce: RatingID (PK), UserID (FK), SongID (FK), RatingValue

---

## Vazby mezi tabulkami:

### Artists k Songs (Umělec k Písni)

- Máme M:N vazbu mezi umělci a písněmi, kde jeden umělec může mít více písní.

### Genres k Songs (Žánr k Písni)

- Máme M:N vazbu mezi žánry a písněmi, kde jedna píseň může patřit k více žánrům a jeden žánr může mít více písní.

### Users k Comments (Uživatel k Komentáři)

- Máme 1:M vazbu mezi uživateli a komentáři, kde jeden uživatel může napsat více komentářů, ale jeden komentář patří jen
  jednomu uživateli.

### Songs k Comments (Píseň k Komentáři)

- Máme 1:M vazbu mezi písněmi a komentáři, kde jedna píseň může mít více komentářů, ale jeden komentář patří jen jedné
  písni.

### Users k Ratings (Uživatel k Hodnocení)

- Máme 1:M vazbu mezi uživateli a hodnoceními, kde jeden uživatel může udělit hodnocení více písním, ale jedno hodnocení
  patří jen jednomu uživateli.

### Songs k Ratings (Píseň k Hodnocení)

- Máme 1:M vazbu mezi písněmi a hodnoceními, kde jedna píseň může mít více hodnocení, ale jedno hodnocení patří jen
  jedné písni.



**Zkratka**: Vysvětlivka pro zkratku.