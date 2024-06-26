param (
    [Parameter(Mandatory = $true)]
    [string]$function,

    [Parameter(Mandatory = $true)]
    [int]$N
)

if ($N -lt 1) {
    Write-Host "Please provide a positive integer value for N."
    exit 1
}

for ($i = 1; $i -le $N; $i++) {
    Write-Host "Running $function for the $i time"
    Invoke-Expression $function
}
