# run.ps1 - Compile and run the Parking Management System
# Usage: .\run.ps1           -> compile + run once
# Usage: .\run.ps1 -Watch   -> watch for changes, recompile & rerun automatically

param(
    [switch]$Watch
)

$compiler = "C:\msys64\ucrt64\bin\g++.exe"
$srcDir   = "$PSScriptRoot\src"
$output   = "$PSScriptRoot\parking_system.exe"

$sources = @(
    "$srcDir\main.cpp",
    "$srcDir\data_structure\linked_list.cpp",
    "$srcDir\data_structure\queue.cpp",
    "$srcDir\data_structure\stack.cpp",
    "$srcDir\algorithm\hashmap.cpp",
    "$srcDir\algorithm\sorting.cpp"
)

function Build {
    Write-Host "`n[BUILD] Compiling..." -ForegroundColor Cyan
    & $compiler -fdiagnostics-color=always -g $sources -o $output -I $srcDir
    return $LASTEXITCODE
}

function Run {
    Write-Host "[RUN] Running parking_system.exe`n" -ForegroundColor Green
    & $output
}

if (-not $Watch) {
    # --- Single run mode ---
    $code = Build
    if ($code -eq 0) { Run }
    else { Write-Host "[ERROR] Build failed." -ForegroundColor Red }
} else {
    # --- Watch mode: auto-recompile on file change ---
    Write-Host "[WATCH] Watching for changes in src\... Press Ctrl+C to stop." -ForegroundColor Yellow

    $lastHash = ""
    $job = $null

    while ($true) {
        # Compute a hash of all source file last-write times
        $currentHash = ($sources | ForEach-Object {
            if (Test-Path $_) { (Get-Item $_).LastWriteTimeUtc.Ticks }
        }) -join ","

        if ($currentHash -ne $lastHash) {
            $lastHash = $currentHash

            # Kill previous run if still alive
            if ($job -and $job.State -eq "Running") {
                Stop-Job $job | Out-Null
                Remove-Job $job | Out-Null
                Write-Host "[WATCH] Previous run stopped." -ForegroundColor DarkYellow
            }

            $code = Build
            if ($code -eq 0) {
                $job = Start-Job -ScriptBlock { param($exe) & $exe } -ArgumentList $output
                Write-Host "[WATCH] Program started (Job $($job.Id)). Waiting for changes..." -ForegroundColor Green
            } else {
                Write-Host "[WATCH] Build failed. Fix errors and save to retry." -ForegroundColor Red
            }
        }

        # Print any output from the running job
        if ($job) {
            Receive-Job $job 2>&1 | Write-Host
        }

        Start-Sleep -Seconds 1
    }
}
