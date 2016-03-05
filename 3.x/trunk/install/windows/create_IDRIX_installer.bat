PATH=%PATH%;C:\Program Files (x86)\Windows Kits\8.1\bin\x86;C:\Program Files (x86)\Inno Setup 5

set BUILDPATH=%~dp0
cd %BUILDPATH%

signtool.exe sign /v /a /n IDRIX /i Thawte /ac C:\Dev\Thawt_CodeSigning_CA.crt /fd sha1 /t http://timestamp.verisign.com/scripts/timestamp.dll ..\..\output\wxFormBuilder.exe ..\..\output\plugins\additional\libadditional.dll ..\..\output\plugins\common\libcommon.dll ..\..\output\plugins\containers\libcontainers.dll ..\..\output\plugins\forms\libforms.dll ..\..\output\plugins\layout\liblayout.dll
signtool.exe sign /v /a /n "IDRIX SARL" /i GlobalSign /ac C:\Dev\GlobalSign_SHA256_EV_CodeSigning_CA.cer /as /fd sha256 /tr http://timestamp.globalsign.com/?signature=sha2 /td SHA256 ..\..\output\wxFormBuilder.exe ..\..\output\plugins\additional\libadditional.dll ..\..\output\plugins\common\libcommon.dll ..\..\output\plugins\containers\libcontainers.dll ..\..\output\plugins\forms\libforms.dll ..\..\output\plugins\layout\liblayout.dll

iscc /Q /Ssigntool81="$qC:\Program Files (x86)\Windows Kits\8.1\bin\x86\signtool$q $p" "wxFormBuilder - IDRIX.iss"

pause