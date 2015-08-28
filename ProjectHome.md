**Currently in the conceptual testing stage.**

## Compilation requirements ##

  * [Alliedmodder's updated HL2 SDK](http://hg.alliedmods.net/) (EP1, or Orange Box Engine)
  * [Metamod:Source Development SDK](http://hg.alliedmods.net/)
  * [MONO runtime v1.9.1\_2](http://www.mono-project.com/Main_Page)
  * [GTK+ 2.1.4 library](http://www.gtk.org/) - dependency removed in future

Currently there are only MAKE files for vs2008/2005.
MAKE files for cross compilation are a TODO.

## Required to run ##

  * [Valve source engine dedicated server](http://www.srcds.com/?knowledge)
> > (visit srcds.com for more info), either linux or windows.

  * [Metamod:source](http://www.sourcemm.net/) installed on the srcds instance
> > configured for monomod via monomod.vdf which is in svn

  * [Mono runtime](http://www.mono-project.com/Main_Page) 1.9.1\_2 or greater

Currently, 4 mono libraries have to be present in the /bin folder of your srcds, or in your OS's environment library search path.
On windows they are: `mono.dll`, `libgthread-2.0-0.dll`, `libglib-2.0-0.dll`, `intl.dll`
These will be located dynamically in the future.

Unhandled exceptions in virtual methods classes inheriting from Mod will crash monomod (which will not crash the server). So catch your exceptions for now.

Remember to close any threads you spawn in `OnUnload` or bad things will happen.