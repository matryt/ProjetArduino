// Variable globale pour stocker l'ID de l'intervalle
var intervalId = null;

function reload() {
    window.location.reload();
}

// Fonction pour démarrer l'intervalle
function startInterval() {
    intervalId = setInterval(reload,  5000);
}

// Fonction pour arrêter l'intervalle
function stopInterval() {
    if (intervalId) {
        clearInterval(intervalId);
        intervalId = null;
    }
}

// Fonction pour initialiser l'intervalle lorsque la page est chargée
function initializeInterval() {
    // Vérifie si la checkbox est cochée et démarre l'intervalle
    var checkbox = document.getElementById("reload");
    if (checkbox.checked) {
        startInterval();
    }
}

// Écouteur d'événements pour la checkbox
document.getElementById("reload").addEventListener("change", function() {
    if (this.checked) {
        startInterval();
    } else {
        stopInterval();
    }
});

// Démarre l'intervalle lorsque la page est chargée
window.addEventListener("load", initializeInterval);