# WSL Setup and C Programming Guide - Fibonacci Sequence

A complete beginner's guide to setting up Windows Subsystem for Linux (WSL) and creating a C program to generate Fibonacci sequences.

## Table of Contents
- [Prerequisites](#prerequisites)
- [Step 1: Enable Windows Features](#step-1-enable-windows-features)
- [Step 2: Install WSL](#step-2-install-wsl)
- [Step 3: Install Ubuntu](#step-3-install-ubuntu)
- [Step 4: Initial Ubuntu Setup](#step-4-initial-ubuntu-setup)
- [Step 5: Install Development Tools](#step-5-install-development-tools)
- [Step 6: Create the Fibonacci Program](#step-6-create-the-fibonacci-program)
- [Step 7: Compile and Run](#step-7-compile-and-run)
- [Troubleshooting](#troubleshooting)
- [Additional Resources](#additional-resources)

## Prerequisites

- Windows 10 version 2004 and higher (Build 19041 and higher) or Windows 11
- Administrator access on your Windows machine
- At least 4GB of free disk space

## Step 1: Enable Windows Features

### Method 1: Using Windows Features Dialog
1. Press `Windows + R` to open the Run dialog
2. Type `optionalfeatures.exe` and press Enter
3. In the Windows Features dialog, check the following boxes:
   - ☑️ **Virtual Machine Platform**
   - ☑️ **Windows Subsystem for Linux**
4. Click **OK** and restart your computer when prompted

### Method 2: Using PowerShell (Alternative)
1. Right-click on Start button and select **Windows PowerShell (Admin)**
2. Run the following commands:
```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```
3. Restart your computer

## Step 2: Install WSL

1. Open **PowerShell as Administrator**
   - Right-click Start button → **Windows PowerShell (Admin)**
2. Run the WSL installation command:
```bash
wsl --install
```
3. If you encounter any issues, try:
```bash
wsl --install -d Ubuntu
```
4. Restart your computer when installation completes

## Step 3: Install Ubuntu

### Method 1: Automatic Installation
If you used `wsl --install`, Ubuntu should be installed automatically. Skip to Step 4.

### Method 2: Manual Installation via Microsoft Store
1. Open **Microsoft Store**
2. Search for **"Ubuntu"**
3. Click on **Ubuntu** (latest LTS version)
4. Click **Install**
5. Wait for the download and installation to complete

## Step 4: Initial Ubuntu Setup

1. Open **Windows Terminal** or search for **Ubuntu** in Start menu
2. Launch Ubuntu for the first time
3. Wait for the initial setup to complete (this may take a few minutes)
4. Create a new user account when prompted:
   ```
   Enter new UNIX username: [your_username]
   New password: [your_password]
   Retype new password: [your_password]
   ```
5. You should now see a terminal prompt like:
   ```
   username@computername:~$
   ```

## Step 5: Install Development Tools

### Update the System
```bash
sudo apt update && sudo apt upgrade -y
```

### Install Build Essential Tools
```bash
sudo apt install build-essential -y
```

### Verify Installation
Check if GCC compiler is installed:
```bash
gcc --version
```
You should see output similar to:
```
gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
```

### Install Additional Useful Tools (Optional)
```bash
sudo apt install git nano vim curl wget -y
```

## Step 6: Create the Fibonacci Program

### Create a New Directory (Optional but Recommended)
```bash
mkdir ~/c_programs
cd ~/c_programs
```

### Create the C Source File
```bash
nano fibonacci_code.c
```

### Add the Fibonacci Program Code
Copy and paste the following code into the nano editor:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

// Function to generate and print Fibonacci sequence
void fibonacci(int n) {
    int a = 0, b = 1, next;
    printf("Fibonacci sequence:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", a);  // Print current term
        next = a + b;      // Calculate next term
        a = b;
        b = next;
    }
    printf("\n");
}

int main() {
    pid_t pid;  // Process ID variable
    int n;      // Number of Fibonacci terms

    // Ask user for input
    printf("Enter the number of Fibonacci terms: ");
    scanf("%d", &n);

    // Create a child process using fork()
    pid = fork();

    // Check if fork() failed
    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;  // Exit with error
    }
    // Child process code
    else if (pid == 0) {
        printf("Child process started (PID: %d)\n", getpid());       // Show child PID
        printf("Parent PID from child process: %d\n", getppid());    // Show parent PID
        fibonacci(n);  // Call Fibonacci function
        printf("Child process exiting.\n");
    }
    // Parent process code
    else {
        printf("Parent process started (PID: %d)\n", getpid());  // Show parent PID
        wait(NULL);  // Parent waits until child process is done
        printf("Parent process waited for child (PID: %d) to complete.\n", pid);
    }

    return 0;
}
```

### Save and Exit Nano Editor
1. Press `Ctrl + O` to save (WriteOut)
2. Press `Enter` to confirm the filename
3. Press `Ctrl + X` to exit nano

### Verify File Creation
```bash
ls -la fibonacci_code.c
cat fibonacci_code.c
```

## Step 7: Compile and Run

### Compile the Program
```bash
gcc fibonacci_code.c -o fibonacci
```

### Check if Compilation was Successful
```bash
ls -la fibonacci
```
You should see an executable file named `fibonacci`.

### Run the Program
```bash
./fibonacci
```

### Sample Output
```
Enter the number of terms in Fibonacci sequence: 10
Fibonacci Series: 0 1 1 2 3 5 8 13 21 34
```

### Test with Different Inputs
Try running the program multiple times with different numbers:
```bash
./fibonacci
# Try with 5, 15, 20, etc.
```

## File Structure
After completing all steps, your directory structure should look like:
```
~/c_programs/
├── fibonacci_code.c    (source code)
└── fibonacci          (executable file)
```

## Troubleshooting

### WSL Installation Issues
- **Error: "WSL 2 requires an update to its kernel component"**
  - Download and install: [WSL2 Linux kernel update package](https://aka.ms/wsl2kernel)
  
- **Ubuntu doesn't start**
  - Try: `wsl --set-default-version 2`
  - Then: `wsl --set-version Ubuntu 2`

### Compilation Issues
- **"gcc: command not found"**
  - Run: `sudo apt install build-essential`
  
- **Permission denied when running ./fibonacci**
  - Run: `chmod +x fibonacci`

### General Linux Commands for Beginners
```bash
pwd                    # Show current directory
ls                     # List files
ls -la                 # List files with details
cd ~                   # Go to home directory
cd ..                  # Go to parent directory
mkdir folder_name      # Create directory
rm filename            # Delete file
rm -r folder_name      # Delete directory
clear                  # Clear terminal screen
```

## Additional Resources

- [WSL Documentation](https://docs.microsoft.com/en-us/windows/wsl/)
- [Ubuntu Command Line Basics](https://ubuntu.com/tutorials/command-line-for-beginners)
- [GCC Compiler Documentation](https://gcc.gnu.org/onlinedocs/)
- [C Programming Tutorial](https://www.learn-c.org/)

## Next Steps

Now that you have WSL set up and can compile C programs, you can:
1. Learn more C programming concepts
2. Create more complex programs
3. Explore other Linux development tools
4. Try different programming languages available in Ubuntu

---

**Note**: This guide assumes you're using Windows 10/11 with WSL 2. Commands and steps may vary slightly depending on your specific Windows version and WSL distribution.
