1. **Návrh tříd a hierarchie**:
    - Pro začátek si představte, jaké typy hodnot JSON budete potřebovat reprezentovat. Máme integer, pole, objekt a null hodnotu.
    - Zvažte, jaké metody a vlastnosti budou potřeba pro každý typ hodnoty. Například, integer bude potřebovat metodu `get_value`, pole bude potřebovat metody `size`, `append` a `remove`, objekt bude potřebovat metody pro práci s klíči a hodnotami jako `keys`, `insert` a `remove`.

2. **Implementace jednotlivých tříd**:
    - Pro každý typ hodnoty JSON vytvořte odpovídající třídu.
    - Zamyslete se nad tím, jak bude každá třída reprezentovat daný typ hodnoty a jaké informace budou uchovávány v objektu.

3. **Memory management**:
    - Použijte STL kontejnery pro ukládání prvků pole a objektů.
    - Správně manipulujte s raw pointery a zajistěte, aby paměť byla dealokována správně. Ujistěte se, že každý prvek pole a objektu vlastní své potomky a odpovídajícím způsobem je dealokuje.

4. **Indexace**:
    - Implementujte operátor `[]` pro indexaci prvků pole a objektů. Dbejte na to, aby indexace byla povolena pouze pro objekty, které ji podporují.
    - Zvažte implementaci odpovídajících výjimek pro případy, kdy je objekt indexován, ale není indexovatelný.

5. **Kopírování**:
    - Implementujte metodu `clone` pro hluboké kopírování objektů.
    - Zvažte návratový typ této metody tak, aby podporoval polymorfní chování.

6. **Operace s jednotlivými typy**:
    - Implementujte metody pro práci s jednotlivými typy hodnot JSON, jako jsou `get_value`, `size`, `append`, `remove`, `keys`, `insert` a `remove`.

7. **Visitor pattern**:
    - Implementujte design pattern Visitor pro přidání nových operací bez změny základní hierarchie tříd.
    - Vytvořte třídu reprezentujícího návštěvníka a implementujte virtuální metodu `accept` v každé třídě týkající se JSON hodnot, která bude delegovat volání na správnou metodu návštěvníka.

8. **Testování**:
    - Vytvořte testy pro ověření funkcionality každé metody a třídy.
    - Testy by měly pokrýt různé scénáře a hraniční případy.

Během implementace se ujistěte, že dodržujete principy OOP, správně řídíte paměť a využíváte vhodné design patterns. Dále se můžete zamyslet nad různými optimalizacemi a zlepšeními implementace, které by mohly vylepšit výkon a údržbu kódu.
