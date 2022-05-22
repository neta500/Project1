사용법

MakeExe.bat을 돌리면 pyinstaller 가 돌아서 파이썬 코드를 실행파일(.exe)로 만들어준다. (파이썬은 기본적으로 실행파일을 만들지 않아서 pyinstaller 라이브러리를 사용)
GenPackets.exe 파일이 생성되면 얘로 Templates폴더에 있는 템플릿들을 읽어와서 알맞게 필요한 파일들을 생성한다. 템플릿 파싱은 파이썬 라이브러리인 jinja2를 사용한다.
