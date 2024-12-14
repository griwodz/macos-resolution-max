// Find the largest sensible resolution on this Mac and change to it.
// Stay at this resolution until a key is pressed.

#include <iostream>
#include <CoreGraphics/CoreGraphics.h>

int main( int argc, const char *argv[] )
{
    auto mainDisplayId = CGMainDisplayID();
    
    std::cout << "Current resolution was "
              << CGDisplayPixelsWide( mainDisplayId ) << 'x'
              << CGDisplayPixelsHigh( mainDisplayId ) << std::endl;
    
    auto modes = CGDisplayCopyAllDisplayModes( mainDisplayId, nullptr );

    CFIndex          c, choice, count;
    CGDisplayModeRef mode;
    size_t           w, h;
    size_t           my_w = 0;

    count  = CFArrayGetCount( modes );
    choice = -1;

    for( c=count; c--; )
    {
        mode = (CGDisplayModeRef)CFArrayGetValueAtIndex( modes, c );
        w    = CGDisplayModeGetWidth( mode );
        h    = CGDisplayModeGetHeight( mode);

        auto refresh = CGDisplayModeGetRefreshRate( mode );
        auto usable  = CGDisplayModeIsUsableForDesktopGUI( mode );
        if( refresh == 60.0 && h == 1600 && w > my_w )
        {
            std::cout << "Selecting resolution mode "
                      << w << 'x' << h
                      << " refresh rate " << refresh << std::endl;;
            choice = c;
        }
    }

    if( choice >= 0 )
    {
        mode = (CGDisplayModeRef)CFArrayGetValueAtIndex( modes, choice );
        w    = CGDisplayModeGetWidth( mode );
        h    = CGDisplayModeGetHeight( mode );

        std::cout << "Changing to " <<  w << "x" << h << std::endl;

        CGDisplaySetDisplayMode( mainDisplayId, mode, nullptr );

        std::cout << "Waiting for keypress" << std::endl;
        std::cin.get();
    }
    return 0;
}

