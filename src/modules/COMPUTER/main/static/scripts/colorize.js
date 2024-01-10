window.onload = function() {
    var divs = document.querySelectorAll('.alert'); // sélectionnez tous les divs

    divs.forEach(function(div) {
    var texte = div.querySelectorAll("p")[1].innerText; // obtenez le texte du div

    if(texte === 'Unknown face. Danger !') {
        div.classList.add('bck-red'); // ajoutez la classe rouge si le texte correspond
    } else {
        div.classList.add('bck-green'); // sinon, ajoutez la classe verte
    }
    });
    }