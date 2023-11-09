document.getElementById('getCatButton').addEventListener('click', function() {
    var apiKey = 'live_L5mZaK5l4upMSzNqTVU1I1EHESniFDB8OMbWao2Gekq0WmjgPEQA1pKPp8BgUqmq';
    var apiUrl = 'https://api.thecatapi.com/v1/images/search';

    fetch(apiUrl, {
        headers: {
            'x-api-key': apiKey
        }
    })
        .then(response => response.json())
        .then(data => {
            var catImageElement = document.getElementById('catImage');
            catImageElement.src = data[0].url;
        })
        .catch(error => console.log('Chyba:', error));
});
