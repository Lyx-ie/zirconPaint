#include "masterInclude.h"
std::string sSelectedFile;
std::string sFilePath;
bool openFile()
{
    {
        //  CREATE FILE OBJECT INSTANCE
        HRESULT f_SysHr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (FAILED(f_SysHr))
            return FALSE;

        // CREATE FileOpenDialog OBJECT
        IFileOpenDialog* f_FileSystem;
        f_SysHr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&f_FileSystem));
        if (FAILED(f_SysHr)) {
            CoUninitialize();
            return FALSE;
        }

        //  SHOW OPEN FILE DIALOG WINDOW
        f_SysHr = f_FileSystem->Show(NULL);
        if (FAILED(f_SysHr)) {
            f_FileSystem->Release();
            CoUninitialize();
            return FALSE;
        }

        //  RETRIEVE FILE NAME FROM THE SELECTED ITEM
        IShellItem* f_Files;
        f_SysHr = f_FileSystem->GetResult(&f_Files);
        if (FAILED(f_SysHr)) {
            f_FileSystem->Release();
            CoUninitialize();
            return FALSE;
        }

        //  STORE AND CONVERT THE FILE NAME
        PWSTR f_Path;
        f_SysHr = f_Files->GetDisplayName(SIGDN_FILESYSPATH, &f_Path);
        if (FAILED(f_SysHr)) {
            f_Files->Release();
            f_FileSystem->Release();
            CoUninitialize();
            return FALSE;
        }

        //  FORMAT AND STORE THE FILE PATH
        std::wstring path(f_Path);
        std::string c(path.begin(), path.end());
        sFilePath = c;

        //  FORMAT STRING FOR EXECUTABLE NAME
        const size_t slash = sFilePath.find_last_of("/\\");
        sSelectedFile = sFilePath.substr(slash + 1);

        //  SUCCESS, CLEAN UP
        CoTaskMemFree(f_Path);
        f_Files->Release();
        f_FileSystem->Release();
        CoUninitialize();
        return TRUE;
    }
}

std::string returnFilePath() {
    return sFilePath;
}

int incorrectFileTypeDialogueBox()
{
    {
        int msgboxID = MessageBox(
            NULL,
            L"This file type is not supported, Please choose one from: bmp, png, tga, jpg, gif, psd, hdr, pic and pnm.",
            L"ERROR",
            MB_ICONEXCLAMATION | MB_OK
        );

        return msgboxID;
    }
}

int incorrectFileTypeDialogueBox2()
{

    int msgboxID = MessageBox(
        NULL,
        L"You don't have a valid image selected for the Stamp Tool. Select an image with the drop down and try again.",
        L"ERROR",
        MB_ICONEXCLAMATION | MB_OK
    );

    return msgboxID;

}

