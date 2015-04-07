# Introduction #

NairnMPM has a customizable archive method. This page explains how to add an option to archive a new quantity from the calculation results. This page also explains how to [add a new quantity](#Add_Global_Archive_Quantity.md) to the global archiving feature.

# Basic Steps #

  1. Create new constant and add to archive constants in `ArchiveData.hpp`
    * Put particle property before `ARCH_MAXMPMITEMS`
    * Put crack property before `ARCH_MAXCRACKITEMS`
  1. In `ArchiveData` class
    * Add default archiving setting in constructor for new option to default archiving order. This is the order and content used if the XML input file does not specify an order.
    * Add size calculation in `ArchiveData::CalcArchiveSize()` for new item
  1. If new option is a material point property then archive in `ArchiveData` class by:
    * Add writing option in `ArchiveData::ArchiveResults()` for new item
    * Add reversing option in `ArchiveData::ArchiveResults()` for new item
  1. If new option is a crack property then archive in `ArchiveData` class by:
    * Add writing option in `ArchiveData::FillArchive()`
    * Add reversing option in `ArchiveData::FillArchive()`

# Add Global Archive Quantity #

The method to add global quantity for archiving is explained in comments at the start of `GlobalQuantity.cpp`'