#take sourcefile as argument
$sourceFile = $args[0]
#remove the extension and folders from the source file
$outputFile = $sourceFile -replace '\.cpp', '.exe' -replace '^.+\\', ''
# Compile the C++ file
$compileCommand = "g++ -o ./output/$outputFile -I ./include $sourceFile" 
Invoke-Expression $compileCommand

# Check if the compilation was successful
if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful. Running the executable..."
    Write-Host $outputFile
    # Run the executable
    Invoke-Expression ./output/$outputFile
} else {
    Write-Host "Compilation failed."
}