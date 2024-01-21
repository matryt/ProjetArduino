document.getElementById("delete-all-alerts").onchange = function() {
    document.getElementById('delete-alerts').disabled = this.checked;
    document.getElementById('delete-alerts').readOnly = this.checked;
    document.getElementById('delete-alerts').value = "";
}

document.getElementById("delete-all-history").onchange = function() {
    document.getElementById('delete-history').disabled = this.checked;
    document.getElementById('delete-history').readOnly = this.checked;
    document.getElementById('delete-history').value = "";
}