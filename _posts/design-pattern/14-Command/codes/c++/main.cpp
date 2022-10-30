#include "./Project/DocumentManager.h"
#include "./Commands/CommandManager.h"
#include "./Commands/FileImport.h"
#include "./Commands/FileAppend.h"
#include "./Commands/FileReadContent.h"

using namespace TMIOSDP;

int main()
{
    DocumentManager docManager;
    CommandManager commands;

    commands.Do(new FileImport(&docManager));

    for (Document* doc : docManager.mDocuments)
    {
        doc->open(std::ios::in);
        doc->describe();
        doc->close();
    }

    Document* firstDoc = docManager.mDocuments.front();

    FileReadContent readCommand(firstDoc);
    readCommand.Execute();
    
    // Let's imagine the input field has been populated from GUI TextEdit and
    // finally, we are goint to submit the data
    commands.Do(new FileAppend(firstDoc, "\nHello, it's me"));
    commands.Do(new FileAppend(firstDoc, "\nHow are you doing?"));
    
    readCommand.Execute();

    commands.Undo();
    readCommand.Execute();

    commands.Undo();
    readCommand.Execute();
}