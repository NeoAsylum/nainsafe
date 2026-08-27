# Schritt 1 von 3 -- WSL2 nachruesten. Braucht Administratorrechte.
#
#   Rechtsklick auf PowerShell -> "Als Administrator ausfuehren", dann:
#   powershell -ExecutionPolicy Bypass -File .\einrichtung\1-wsl-installieren.ps1
#
# Danach ist eine Ubuntu-Distribution installiert, aber noch ohne Benutzer.
# Den legst du in Schritt 2 an -- das Passwort waehlst du selbst, es taucht
# nirgends in diesen Skripten auf.

# Bewusst nicht "Stop": Dieses Skript besteht fast nur aus Aufrufen von wsl.exe.
# In Windows PowerShell 5.1 verpackt eine stderr-Umleitung die Ausgabe eines nativen
# Befehls in ErrorRecords, die "Stop" als Abbruchgrund wertet -- auch wenn der Befehl
# erfolgreich war. Exitcodes werden hier stattdessen einzeln geprueft.
$ErrorActionPreference = "Continue"

$pr = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
if (-not $pr.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Write-Host "Dieses Skript braucht Administratorrechte." -ForegroundColor Red
    Write-Host "PowerShell als Administrator oeffnen und erneut starten."
    exit 1
}

Write-Host "== 1/3  WSL2 einrichten ==" -ForegroundColor Cyan

Write-Host "`n[1] WSL-Kernel aktualisieren ..." -ForegroundColor Yellow
wsl --update
if ($LASTEXITCODE -ne 0) { Write-Host "wsl --update meldete Code $LASTEXITCODE." -ForegroundColor Red }

Write-Host "`n[2] Vorhandene Distributionen:" -ForegroundColor Yellow
# Ohne stderr-Umleitung: wsl.exe meldet "keine Distributionen" auf stderr mit
# Exitcode -1, was hier ein gueltiger Zustand ist und kein Fehler.
$distros = (wsl --list --quiet | Out-String)
if ($distros -match "Ubuntu") {
    Write-Host "    Ubuntu ist bereits installiert -- Installation uebersprungen."
} else {
    Write-Host "    Keine gefunden. Installiere Ubuntu (ohne Autostart) ..."
    wsl --install -d Ubuntu --no-launch
    if ($LASTEXITCODE -ne 0) {
        Write-Host "`nInstallation meldete Code $LASTEXITCODE." -ForegroundColor Red
        Write-Host "Haeufigste Ursache: Virtualisierung ist im BIOS/UEFI deaktiviert."
        Write-Host "Pruefen im Task-Manager -> Leistung -> CPU -> 'Virtualisierung'."
        exit 1
    }
}

Write-Host "`n[3] Status:" -ForegroundColor Yellow
wsl --list --verbose

Write-Host "`n== Fertig. Weiter mit Schritt 2 ==" -ForegroundColor Green
Write-Host @"

Falls Windows einen Neustart verlangt: neu starten, dann hier weiter.

Naechster Schritt -- Ubuntu zum ersten Mal starten und deinen Benutzer anlegen:

    wsl -d Ubuntu

Ubuntu fragt nach Benutzername und Passwort. Das Passwort brauchst du fuer sudo;
notiere es. Danach in der Ubuntu-Shell:

    bash /mnt/c/Users/adria/OneDrive/Desktop/nainsafe/nainsafe/einrichtung/2-fabrik-aufsetzen.sh

"@ -ForegroundColor Gray
