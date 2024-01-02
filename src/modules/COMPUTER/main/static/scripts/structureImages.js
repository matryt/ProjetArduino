// Récupérez tous les divs .alert
let alertDivs = Array.from(document.querySelectorAll('.alert'));

// Créez un nouveau div #first et ajoutez-y le premier .alert
let firstDiv = document.createElement('div');
firstDiv.id = 'first';
firstDiv.appendChild(alertDivs.shift()); // Shift remove le premier élément du tableau et le retourne

// Créez un nouveau div #other et ajoutez-y les autres .alert
let otherDiv = document.createElement('div');
otherDiv.id = 'other';

// Ajoutez chaque .alert restant à #other
alertDivs.forEach(function(alertDiv) {
 otherDiv.appendChild(alertDiv);
});

// Créez un nouveau div #all et ajoutez-y #first et #other
let allDiv = document.createElement('div');
allDiv.id = 'all';
allDiv.appendChild(firstDiv);
allDiv.appendChild(otherDiv);

// Remplacez le div #all existant par le nouveau
let oldAllDiv = document.getElementById('all');
oldAllDiv.parentNode.replaceChild(allDiv, oldAllDiv);