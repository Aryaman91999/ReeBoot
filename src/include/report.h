#ifndef REPORT_H
#define REPORT_H

static inline EFI_STATUS Report(EFI_STATUS Status, CHAR16 *Msg) {
    Print(L"Unexpected Error: %s (EFI %r)\n", Msg, Status);
    return Status;
}

#endif //REPORT_H
