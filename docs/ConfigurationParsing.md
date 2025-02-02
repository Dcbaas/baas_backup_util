# Introduction
This describes how the utility parses configurations

# Details
The configuration points to the 7zip executable. In this first iteration, the app will execute an external 7z exe to perform the backup. Later versions of this app will have the lzma libraries included in the app itself 

The configuration will accept a list of inputs (aka folders). The input is a json which has the path to the folder along with a flag to indicate if the folder will be scanned recursively (will all subfolder be scanned). There has to be one or more inputs defined.

The configuration will accept multiple output paths. A backup can be copied to multiple locations if needed 

A sample config is located at docs/example-configuration.json
```
{
    "7zipExec": "C:\\Program Files\\7-Zip\\7z.exe",
    "inputs": [
        {
            "path": "C:\\Path\\Here",
            "recursive": true
        },
        {
            "path": "C:\\Path\\Here2"
        }
    ],
    "outputs": [
        "C:\\Output\\Path\\Here",
        "C:\\Output\\Path\\Here2"
    ]
}
```