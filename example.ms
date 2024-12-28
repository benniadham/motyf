module acme.main;

import ltd.fmt;

/**
 * Point represents a point in the 3D space
 */
type Point : class {
    var x : int;
    var y : int;
    var name : String;

    pub func getCoordinate : () -> (int, int | Status) const 
    {
        return x, y, Status.Ok;
    }

    pub func setCoordinate : (x : int, y : int) -> Status
    {
        self.x = x;
        self.y = y;

        return Status.Ok;
    }

    pub func setName : (in name : String) -> Status
    {
        self.name = name;

        return Status.Ok;
    }
};

// Get the origin of a point;
func origin : (out ori : Point) -> Status
{
    ori.setCoordinate(0, 0);
    ori.setName("Point of origin");

    return Status.Ok;
}

func main : () -> int
{
    var p = new Point(10, 10);

    fmt.println("%d, %d", p.getCoordinate()) 
        | Status.ErrEmptyCoordinate => fmt.println("Coordinate is empty")
        | Status.NullException => fmt.println("Cannot process null coordinate");

    return 0;
}

