document.getElementById("delete-all-history").onchange = function() {
    document.getElementById('delete-history').disabled = this.checked;
    document.getElementById('delete-history').readOnly = this.checked;
    document.getElementById('delete-history').value = "";
}