#include "Library.h"

void addBooks(Library *Library)
{
    Library->addBook(12345, "The Nightingale", "Kristin Hannah", "St. Martin's Press", 2015);
    Library->addBook(67890, "The Alchemist", "Paulo Coelho", "HarperOne", 1988);
    Library->addBook(24680, "The Martian", "Andy Weir", "Crown Publishing Group", 2011);
    Library->addBook(13579, "A Game of Thrones", "George R.R.Martin", "Bantam Spectra", 1996);
    Library->addBook(98765, "Educated", "Tara Westover", "Random House", 2018);
    Library->addBook(55555, "The Hunger Games", "Suzanne Collins", "Scholastic Press", 2008);
    Library->addBook(11111, "The Catcher in the Rye", "J.D.Salinger", "Little, Brown and Company", 1951);
    Library->addBook(44444, "To Kill a Mockingbird", "Harper Lee", "J.B.Lippincott & Co.", 1960);
    Library->addBook(77777, "1984", "George Orwel", "Secker & Warburg", 1949);
    Library->addBook(22222, "The Picture of Dorian Gray", "Oscar Wilde", "Lippincott's Monthly Magazine", 1890);
}

void addEBooks(Library *Library)
{
    Library->addEBook(6, "The Catcher in the Rye", "J.D.Salinger", "Little, Brown and Company", 1951, "PDF", "1.5 MB");
    Library->addEBook(7, "One Hundred Years of Solitude", "Gabriel García Márquez", "HarperCollins", 1967, "MOBI", "2.5 MB");
    Library->addEBook(8, "The Great Gatsby", "F.Scott Fitzgerald", "Scribner", 1925, "AZW", "1.8 MB");
    Library->addEBook(9, "The Da Vinci Code", "Dan Brown", "Doubleday", 2003, "EPUB", "3 MB");
    Library->addEBook(4, "The Alchemist", "Paulo Coelho", "HarperOne", 1988, "PDF", "1.2 MB");
}

void addAudioBooks(Library *Library)
{
    Library->addAudioBook(104, "Harry Potter and the Philosopher's Stone", "J.K. Rowling", "Pottermore Publishing", 2015, "Stephen Fry", "8 hours and 44 minutes");
    Library->addAudioBook(105, "The Lord of the Rings: The Fellowship of the Ring", "J.R.R.Tolkien", "Recorded Books", 2001, "Rob Inglis", "19 hours and 11 minutes");
    Library->addAudioBook(106, "The Hitchhiker's Guide to the Galaxy", "Douglas Adams", "Random House Audio", 2005, "Stephen Fry", "5 hours and 51 minutes");
    Library->addAudioBook(107, "The Girl with the Dragon Tattoo", "Stieg Larsson", "Random House Audio", 2008, "Saul Reichlin", "16 hours and 33 minutes");
    Library->addAudioBook(108, "Pride and Prejudice", "Jane Austen", "Blackstone Audio", 2008, "Kate Reading", "11 hours and 35 minutes");
}

void addMedia(Library *Library)
{
    /*Library->addCD(92837, "Thriller", 9);
    Library->addCD(78543, "Back in Black", 10);
    Library->addCD(63218, "The Dark Side of the Moon", 9);
    Library->addCD(41359, "Appetite for Destruction", 12);
    Library->addCD(4786, "Nevermind", 12);*/

    Library->addDVD(6541, "The Godfather", "175 min");
    Library->addDVD(2398, "Pulp Fiction", "154 min");
    Library->addDVD(8210, "The Shawshank Redemption", "142 min");
    Library->addDVD(4132, "The Dark Knight", "152 min");
    Library->addDVD(9476, "Forrest Gump", "142 min");
}

void addData(Library *Library)
{
    addBooks(Library);
    addEBooks(Library);
    addAudioBooks(Library);
    addMedia(Library);
}