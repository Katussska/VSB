
- **HTTP** - Hyper Text Transfer Protocol

### URL
- URL (Uniform Resource Locator) je odkaz nebo adresa používaná k přístupu k zdrojům na internetu. 

`https://www.priklad.com:420/jsi/kokot?delka=18cm&zakriveni=15deg#fotka`
1. Schema
	- oznacuje protokol pouzity k pristupu ke zdroji, napr. http, https, ftp, malto atd
	- `https`
2. Host
	- domenove jmeno nebo ip adresa serveru
	- `www.priklad.com`
3. Port
	- optional
	- `:420`
4. Path
	- umisteni souboru na serveru, nekdy oznacovano jako route
	- `/jsi/kokot`
5. Query parameters
	- parametry dotazu, key - value
	- `?delka=18cm&zakriveni=15deg`
6. Fragment
	- konkretni sekvence uvnitr zdroje, oznaceni kotva nebo has
	- `#fotka`

#### Jak typicky vypadá (co obsahuje) hlavička HTTP požadavku?

- **Host:** Specifikuje internetovou doménu a port serveru.
- **User-Agent:** Informace o softwaru, který odesílá požadavek.
- **Accept:** Typy médií (MIME), které klient podporuje.
- **Content-Type:** Typ obsahu, který je součástí požadavku (například při odesílání dat formuláře).

```
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Content-Type: application/json
```

- **Authorization:** Používá se pro přenos informací o ověření (například při použití HTTP Basic Auth).
- **Cookie:** Informace o cookies, které jsou uloženy na straně klienta.
- **Referer:** URL odkazující na aktuální stránku.
- **Content-Length:** Velikost datového těla požadavku.
#### Napište pomocí CSS specifikaci pro nastavení šedé barvy písma a tučného písma pro odkaz s přidělenou třídou „odkaz“ (kdekoliv na stránce). Uvedený styl platí jen v případě, že je nad odkazem aktuálně umístěn kurzor myši:

```css
a.odkaz:hover {
	color: gray;
	font-weight: bold;
}
```

##### Napište JavaScript kód, příp. HTML kód (můžete použít čistý JavaScript i JQuery Framework) tak, aby se po kliknutí na odkaz nastavil obsah elementu DIV s identifikátorem „info“ na hodnotu „Kliknuto“.
```html
<div id="info">blablabla</div>
<a onclick="document.getElementById('info').innerHTML = 'Kliknuto'">odkaz</a>
```

##### Co znamená zkratka DOM (z pohledu webových stránek) a k čemu se používá? 

Zkratka "DOM" v kontextu webových stránek označuje "Document Object Model" neboli "Model dokumentu jako objekt." DOM je reprezentace dokumentu (například HTML nebo XML) jako stromové struktury, kde každý uzel představuje část dokumentu, jako jsou elementy, atributy a textové uzly. DOM poskytuje programátorské rozhraní, které umožňuje dynamicky měnit obsah, strukturu a styl webových stránek.

##### Napište XPath dotaz pro výběr pouze obsahu všech elementů s názvem „moznost“:
```xml
<?xml version="1.0" encoding="utf-8"?>
<anketa>  
	<otazka>Kolik hodin strávíte denně u počítače?</otazka> 
	<moznosti> 
		<moznost hlasu='12'>12-15 hodin</moznost>
		 <moznost hlasu='5'>15-20 hodin</moznost>
		 <moznost hlasu='15'>20-24 hodin</moznost>
		 <moznost hlasu='10'>Můj počítač nefunguje</moznost>
	</moznosti>
 </anketa>
```

```
//moznost/text()
```
https://www.w3schools.com/xml/xpath_syntax.asp

#### Co je to stavový kód (alespoň 3)
- je číselný kód, který webový server vrací jako součást odpovědi na HTTP požadavek. Tento kód informuje klienta (například webový prohlížeč), jak proběhla žádost. 

- `200` OK
- `400` Bad request
- `401` Unauthorized
- `403` Forbidden
- `404` Not Found
- `500` Internal server error
- `502` Baf Gateway
- `503` Service unavailable
- `418` I'm a teapot

##### Kategorie
-  [1xx: Informational](https://http.dev/status#1xx-informational)  
- [2xx: Success](https://http.dev/status#2xx-success)  
- [3xx: Redirection](https://http.dev/status#3xx-redirection)  
- [4xx: Client error](https://http.dev/status#4xx-client-error)  
- [5xx: Server error](https://http.dev/status#5xx-server-error)

https://http.dev/status

### co jsou to media queries + priklad
- umožňují aplikovat různé styly nebo layouty na stránce v závislosti na vlastnostech zařízení nebo okolního prostředí, jako jsou šířka obrazovky, rozlišení, orientace, a další
- uziva se pro responzivni design

```css
@media only screen and (max-width: 600px) {}
```

#### CSS styl pro pozadi a velikost pisma talacitka + zmena pozadi pri najeti mysi

```css
button {
	background: black;
	font-size: 13px;
}

button:hover {
	background: blue;
}
```

#### JS vytvoreni noveho elementu `span` s tridou 'box' a textem 'neliknuto' + pridani listenera pri kliknuti zmenit text na 'kliknuto'

```js
let kkt = document.createElement('span')
kkt.setAttribute('class', 'box')
// nebo
kkt.classList.add('box')
kkt.innerHTML = 'nekliknuto'

kkt.addEventListener('click', (e) => {
	e.target.innerHTML = 'kliknuto'
})
```

#### nove elementy HTML5 (alespon 4)

- article
- footer
- nav
- video
- audio