Úkol

Vaším úkolem bude implementovat hierarchii popisující JSON dokument. Jedná se o cvičení v modelování dokumentu (hierarchie obsahující různé typy prvků) pomocí přístupu vanilla OOP s polymorfismem. Můžete se pokusit také modelovat tento dokument jiným způsobem, například pomocí std::variant. Uvidíme později, že takový přístup může být ergonomičtější.

Abstraktní prvek dokumentu bude reprezentován třídou Value. Použijte OOP k modelování JSON dokumentů, které mohou obsahovat:

    Celé číslo (Integer)
    Pole JSON prvků (Array)
    Objekt s řetězcovými klíči (Object)
    Hodnotu null reprezentující nedostatek hodnoty (Null)

Níže najdete komentáře týkající se implementace a požadovaných funkcí (viz také testy). Přemýšlejte o kompromisních, se kterými se setkáte při implementaci dokumentu pomocí OOP, a zahrňte komentář do příspěvku, který popíše vaše zkušenosti.

Jsou zde některé otázky označené [*] - zkopírujte tyto otázky do nějakého komentáře v souboru tasks.h a odpovězte na ně ve svém příspěvku (můžete na ně také odpovědět pomocí systému Kelvinových komentářů).
Správa paměti

Můžete použít kontejnery STL pro ukládání prvků pole (např. std::vector) a prvků objektu (nějaký druh mapy nebo stromu). Zatím nepoužívejte chytré ukazatele, uchovávejte v kontejnerových prvcích (pole/objekt) raw pointery a řádně se starat o dealokaci paměti. Kontejnerové prvky by měly dostat své potomky jako raw pointery a v tu chvíli se stanou jedinečnými vlastníky těchto ukazatelů (budou zodpovědní za jejich smazání). Nemusíte implementovat podporu pro kopírování/přiřazení dokumentu, místo toho se ujistěte, že kopírování/přiřazení bude úplně zakázáno. [] Mohou být jednotlivé prvky sdíleny mezi různými JSON kontejnery (pole/objekt) s uvedeným návrhem? Můžete vzít jeden konkrétní prvek (např. celé číslo) alokovaný na haldě a umístit ho jak do pole, tak do objektu? [] Mohly by být použity reference (nebo ukazatele, které nejsou vlastníkem) k ukládání prvků v JSON kontejnerech? Jak by to ovlivnilo použitelnost polí a objektů? Vyzkoušejte to a podívejte se, jak snadné nebo obtížné to je :)
Indexování

Bude možné indexovat každý JSON prvek jak číselným indexem, tak řetězcem pomocí operátoru [] . Tyto indexovací operace budou pouze pro čtení. [] Není-li možné indexovat objekty, vyvolá výjimku při pokusu o indexování pomocí operátoru []. Můžete použít výjimku z standardní knihovny, ale raději vytvořte vlastní výjimku, pokud je to možné. Použijte název, který považujete za vhodný pro výjimku, testy kontrolují pouze to, zda je vyvolána výjimka, ne jaký typ výjimky to je. [] Přemýšlejte o této rozhraní. Jaké jsou jeho výhody nebo nevýhody? Je lepší umístit indexéry do kořenového prvku Value? Nebo by měly být podporovány pouze typy, které skutečně implementují indexaci (pole/objekty)? Přemýšlejte o kompromisních (kompilační časová bezpečnost vs. ergonomie). [*] Přemýšlejte o návratovém typu. Co by to mělo být? Je zde nutné použít std::optional?
Kopírování

Bude možné zkopírovat (klonovat) každý JSON prvek pomocí metody clone. To představí hlubokou kopii, která zkopíruje všechny obsažené prvky. Viz návrhový vzor Prototype. [*] Jak můžete implementovat kopírování pro polymorfní objektovou hierarchii? Jaký by měl být návratový typ metody clone? Pokud máte zájem, podívejte se na "C++ kovarianci".
Celá čísla

Objekty typu Integer budou mít metodu get_value, která vrátí jejich aktuální hodnotu.