#include "src/headers/data.h" // víc jak 3 třídy - user, librarian, registered user, book, ebook, audiobook, library, media, cd, ...

int main()
{
    // 1. Zadání (jiné než z přednášek) si vymyslíte sami, projekt ale musí obsahovat minimálně sedm tříd.
    // 2. Projekt bude obsahovat kompozice (hierarchie) objektů.
    // 3. Projekt bude obsahovat a používat přetížené metody.
    // 4. Projekt bude obsahovat a používat třídu v roli objektu.
    // 5. Projekt bude obsahovat a využívat dědičnou hierarchii obsahující alespoň tři třídy.
    // 6. Dědičnost bude obsahovat a používat jak rozšíření (dat i metod), tak změnu chování s využitou pozdní vazbou.
    // 7. Dědičná hierarchie bude obsahovat čistě abstraktní třídu.
    // 8. Projekt bude využívat polymorfismus (polymorfní přiřazení i polymorfní datovou strukturu).
    // 9. Po spuštění projektu bude vytvořeno alespoň několik desítek objektů zahrnujících objekty všech deklarovaných tříd (s výjimkou abstraktních) a ve výpisu na konzole budou prezentovány výsledky úloh, které objekty vykonají.

    // třídy v roli objektů (vše below) a taky několik desítek objektů konající nějaké činnosti:
    Library *Knihovna = new Library("Velká knihovna");

    Librarian *librarian1 = Knihovna->hireLibrarian("Anna Nováková", "Praha 5, Na Hřebenkách 34", 1, 30000);
    Librarian *librarian2 = Knihovna->hireLibrarian("Petr Horák", "Brno, Lidická 23", 2, 25000);
    Librarian *librarian3 = Knihovna->hireLibrarian("Lucie Veselá", "Ostrava, Vítkovická 87", 3, 35000);

    User *user1 = Knihovna->addUser("John Smith", "123 Main St, Anytown USA");
    User *user2 = Knihovna->addUser("Jane Doe", "456 Elm St, Anytown USA");
    User *user3 = Knihovna->addUser("Bob Johnson", "789 Oak Ave, Anytown USA");
    User *user4 = Knihovna->addUser("Samantha Lee", "321 Maple St, Anytown USA");
    User *user5 = Knihovna->addUser("David Kim", "654 Pine Rd, Anytown USA");
    User *user6 = Knihovna->addUser("Oliver Twist", "123 Sunny Rd, Anytown USA");
    User *user7 = Knihovna->addUser("Martha Jinkies", "456 Rose Rd, Anytown USA");
    User *user8 = Knihovna->addUser("Adam Something", "789 Soup Rd, Anytown USA");
    User *user9 = Knihovna->addUser("Martin Luther", "112 Beer Rd, Anytown USA");
    User *user10 = Knihovna->addUser("Chad Giga", "113 Duck Rd, Anytown USA");
    User *user11 = Knihovna->addUser("John Wick", "114 Chicken Rd, Anytown USA");
    User *user12 = Knihovna->addUser("Ryan Gosling", "116 Low Rd, Anytown USA");
    User *user13 = Knihovna->addUser("Pete Repete", "117 Weed Rd, Anytown USA");

    RegisteredUser *regUser1 = Knihovna->addRegisteredUser("John Doe", "123 Main St, Anytown USA", 456789, 555491234, "john.doe@example.com", "p@ssw0rd");
    RegisteredUser *regUser2 = Knihovna->addRegisteredUser("Jane Smith", "456 Elm St, Smallville USA", 789012, 555495678, "jane.smith@example.com", "qwerty");
    RegisteredUser *regUser3 = Knihovna->addRegisteredUser("Bob Johnson", "789 Oak St, Bigcity USA", 345678, 555499012, "bob.johnson@example.com", "password123");
    RegisteredUser *regUser4 = Knihovna->addRegisteredUser("Alice Lee", "321 Pine St, Countryside USA", 901234, 555493456, "alice.lee@example.com", "letmein");
    RegisteredUser *regUser5 = Knihovna->addRegisteredUser("David Brown", "654 Maple St, Seaside USA", 234567, 555497890, "david.brown@example.com", "abc123");
    RegisteredUser *regUser6 = Knihovna->addRegisteredUser("Adam Otherthing", "133 Sunny St, Seaside USA", 234567, 555497890, "david.brown@example.com", "abc1234");
    RegisteredUser *regUser7 = Knihovna->addRegisteredUser("Sam Wide", "466 Rose St, Seaside USA", 963567, 455297490, "aaa@example.com", "abc12345");
    RegisteredUser *regUser8 = Knihovna->addRegisteredUser("Ian Smith", "799 Soup St, Seaside USA", 277567, 563293390, "bbb@example.com", "abc12367");
    RegisteredUser *regUser9 = Knihovna->addRegisteredUser("Maria Smith", "100 Beer St, Seaside USA", 134067, 625400890, "ccc@example.com", "abc12389");
    RegisteredUser *regUser10 = Knihovna->addRegisteredUser("Walter White", "101 Duck St, Seaside USA", 964467, 98540890, "ddd@example.com", "abc12310");
    RegisteredUser *regUser11 = Knihovna->addRegisteredUser("Jesse James", "102 Chicken St, Seaside USA", 124567, 15563890, "eee@example.com", "abc12311");
    RegisteredUser *regUser12 = Knihovna->addRegisteredUser("Ash Ketchum", "457 Low St, Seaside USA", 36867, 305097890, "fff@example.com", "abc12312");
    RegisteredUser *regUser13 = Knihovna->addRegisteredUser("Darren Swift", "888 Weed St, Seaside USA", 235557, 885897890, "ggg@example.com", "abc12313");

    addData(Knihovna);

    Knihovna->borrowBook(user10, 11111);
    Knihovna->borrowBook(user10, 24680);
    Knihovna->borrowBook(user10, 22222);

    user10->printBorrowedBooks();

    std::cout << std::endl;

    Knihovna->borrowBook(user10, 11111);

    Knihovna->returnBook(user10, 22222);

    std::cout << std::endl;

    user10->printBorrowedBooks();

    std::cout << std::endl;

    Knihovna->printLibrarians();

    std::cout << std::endl;

    Knihovna->fireLibrarian(2);

    Knihovna->raiseSalaryToLibratians(23.7);

    std::cout << std::endl;

    Knihovna->printLibrarians();

    std::cout << std::endl;

    std::cout << "Knihy k vypujčení:" << std::endl;
    Knihovna->printAvailableBooks();

    std::cout << std::endl;

    std::cout << "Již vypujčené knihy:" << std::endl;
    Knihovna->printUnavailableBooks();

    std::cout << std::endl;

    Knihovna->printRegisteredUsers();

    std::cout << std::endl;

    Knihovna->deleteRegisteredUser("Sam Wide");
    std::cout << std::endl;

    Knihovna->deleteRegisteredUser(964467); // Walter White
    std::cout << std::endl;

    Knihovna->deleteRegisteredUser("Ash Ketchum");

    std::cout << std::endl;

    Knihovna->printRegisteredUsers();

    return 0;
}
