#ifndef CLIPBOARDSTRINGPROVIDER_H
#define CLIPBOARDSTRINGPROVIDER_H

#include "Abstractions/I_StringProvider.h"
#include <string>
#include <stdexcept>
#include <Windows.h>
#include <Utils/Encoding.h>

class ClipboardStringProvider final : public I_StringProvider {
public:
    ClipboardStringProvider() = default;

    ~ClipboardStringProvider() override = default;

    [[nodiscard]] std::string get_string() override {
        if (!OpenClipboard(nullptr)) {
            throw std::runtime_error("Failed to open clipboard.");
        }

        if (!IsClipboardFormatAvailable(CF_UNICODETEXT)) {
            CloseClipboard();
            throw std::runtime_error("Clipboard does not contain text in UNICODE format.");
        }

        const HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
        if (hClipboardData == nullptr) {
            CloseClipboard();
            throw std::runtime_error("Failed to get clipboard data.");
        }

        const wchar_t *pchData = static_cast<wchar_t *>(GlobalLock(hClipboardData));
        if (pchData == nullptr) {
            CloseClipboard();
            throw std::runtime_error("Failed to lock clipboard data.");
        }

        const std::wstring ws(pchData);
        GlobalUnlock(hClipboardData);
        CloseClipboard();

        return Encoding::utf16_to_utf8(ws);
    }

    void set_string(const std::string &str) override {
        if (!OpenClipboard(nullptr)) {
            throw std::runtime_error("Failed to open clipboard.");
        }

        EmptyClipboard();

        const size_t len = str.size() + 1;
        const HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(wchar_t));
        if (hMem == nullptr) {
            CloseClipboard();
            throw std::runtime_error("Failed to allocate global memory.");
        }

        const auto pMem = static_cast<wchar_t *>(GlobalLock(hMem));
        if (pMem == nullptr) {
            GlobalFree(hMem);
            CloseClipboard();
            throw std::runtime_error("Failed to lock global memory.");
        }

        const auto utf16_str = Encoding::utf8_to_utf16(str);
        wcsncpy_s(pMem, len, utf16_str.c_str(), len - 1);

        GlobalUnlock(hMem);

        if (SetClipboardData(CF_UNICODETEXT, hMem) == nullptr) {
            CloseClipboard();
            throw std::runtime_error("Failed to set clipboard data.");
        }

        CloseClipboard();
    }
};


#endif
