import Graphics.UI.GLUT
import Control.Exception
import System.Exit
import Data.IORef
import System.Random

type Pos  = (GLfloat, GLfloat)
type Area = (GLfloat, GLfloat, GLfloat, GLfloat)

data Direction = ToLeft | ToRight | ToUp | ToDown

data Ship  = Ship { shipPos::Pos, hit::Bool }
data Alien = Alien { alienPos::Pos, speed::GLfloat }
data HitAliensInfo = HitAliensInfo { bullets::[Pos], aliens::[Alien], point::Integer }

interval     = 100
windowWidth  = 320::GLsizei
windowHeight = 240::GLsizei

shapeShip      = [(-10, 0), (0, -10), (10, 0), (10, 10), (-10, 10)]
shapeAlien     = [(-5, -5), (5, -5), (10, 0), (5, 5), (2, 2), (-2, 2), (-5, 5),(-10, 0)]
shapeBullet    = [(-3, -5), (0, -10), (3, -5), (0, 0)]
boundaryShip   = (-10, 0, 10, 10)
boundaryAlien  = (-10, -5, 10, 5)
boundaryBullet = (-3, -10, 3, 0)
colorShip      = Color3 (0.0::Double) 0.0 1.0
colorAlien     = Color3 (1.0::Double) 0.5 0.0
colorScore     = Color3 (1.0::Double) 0.0 0.0
speedAlien     = 5
speedBullet    = 10

initialEnv :: (Area, Ship, [Pos], [Alien], [Pos], Integer, Integer)
initialEnv = 
  (
    (0, 0, convf windowWidth, convf windowHeight),
    Ship (convf $ div windowWidth 2, convf $ div windowHeight 2) False,
    [],
    [],
    [],
    0,
    2
  )

initialAlien = Alien (0, 20) 5

convf :: (Integral a) => a -> GLfloat
convf = fromInteger.toInteger

convd :: (Integral a) => a -> GLdouble
convd = fromInteger.toInteger

includes (x1, y1, x2, y2) (x, y) = and [x1 <= x, x <= x2, y1 <= y, y <= y2]
overlaps lhs@(x1, y1, x2, y2) rhs@(x3, y3, x4, y4) = 
  or [
    includes lhs (x3, y3),
    includes lhs (x3, y4),
    includes lhs (x4, y3),
    includes lhs (x4, y4),
    includes rhs (x1, y1),
    includes rhs (x1, y2),
    includes rhs (x2, y1),
    includes rhs (x2, y2)
  ]
bounds (x1, y1, x2, y2) (x, y) = (x + x1, y + y1, x + x2, y + y2)

moveShip direction (win, ship, sbs, as, abs, score, left) =
  (win, (move direction ship), sbs, as, abs, score, left)
  where
    move ToLeft  (Ship (x, y) b) = Ship (x - 5.0, y) b
    move ToRight (Ship (x, y) b) = Ship (x + 5.0, y) b
    move ToUp    (Ship (x, y) b) = Ship (x, y - 5.0) b
    move ToDown  (Ship (x, y) b) = Ship (x, y + 5.0) b

updateEnv f fs (win, ship, sbs, as, abs, score, left) =
  (win, updateShip, updateBullets, updateAliens, updateAliensBullets, updateScore, updateLeft)
  where
    updateShip          = Ship (shipPos ship) (hitsShip)
    updateBullets       = moveSBullets $ bullets hitsAliens
    updateAliens        = addAlien $ updateAlien $ aliens hitsAliens
    updateAliensBullets = if (hit updateShip) then [] else filter (includes win) $ addBullet (moveABullets abs) as fs
    updateScore         = score + (point hitsAliens)
    updateLeft          = left - if (hit updateShip) then 1 else 0

    hitsShip =
      case (abs, ship) of
        ([], ship) -> False
        (abs, ship) -> or $ map (overlaps (bounds boundaryShip (shipPos ship))) $ map (bounds boundaryBullet) abs
    hitsAliens =
      case (sbs, as) of
        ([], as) -> HitAliensInfo [] as 0
        (sbs@(b:bs), as) ->
          if length leftAliens < length as
              then HitAliensInfo bs leftAliens (toInteger ((length as - length leftAliens) * 10))
              else HitAliensInfo sbs leftAliens 0
            where
              leftAliens = filter overlapsWith as
              overlapsWith a = not $ overlaps (bounds boundaryAlien (alienPos a)) (bounds boundaryBullet b)
    moveSBullets []                = []
    moveSBullets ((pos@(x, y)):bs) = if (includes win pos) 
                                       then (x, y - speedBullet):(moveSBullets bs)
                                       else (moveSBullets bs)
    updateAlien []     = []
    updateAlien (a:as) = (updatePos a):(updateAlien as)
      where
        updatePos (Alien (x, y) dx) =
          if (includes win (x + dx, y)) 
            then Alien (x + dx, y) dx
            else Alien (x, y + speedAlien) (-dx)
    addAlien as = if f == 0 then initialAlien:as else as
    moveABullets []     = []
    moveABullets (b:bs) = (updatePos b):(moveABullets bs)
      where
        updatePos (x, y) = (x, y + speedBullet)
    addBullet bs [] _                      = bs
    addBullet bs ((Alien pos _):as) (f:fs) =
      if f == 0 
        then pos:(addBullet bs as fs)
        else addBullet bs as fs

draw env = do
  (_, ship, sbs, as, abs, score, left) <- readIORef env
  clearColor $= if hit ship then Color4 1.0 0.8 0.8 1.0 else Color4 1.0 1.0 1.0 1.0
  clear [ColorBuffer]
  drawShip $ shipPos ship
  mapM_ (drawBullet colorShip) sbs
  mapM_ drawAlien $ map alienPos as
  mapM_ (drawBullet colorAlien) abs
  drawScore score left
  swapBuffers

drawShip pos = do
  color colorShip
  render shapeShip pos

drawBullet col pos = do
  color col
  render shapeBullet pos

drawAlien pos = do
  color colorAlien
  render shapeAlien pos

drawScore score left = do
{-
  translate $ Vector3 (10::GLfloat) 10 0
  scale (0.1::GLfloat) (-0.1) 0
  color colorScore
  renderString Roman $ "SCORE : " ++ (setw 6 $ show score) ++ " / LEFT : " ++ show left
-}
  putStrLn $ "SCORE : " ++ (setw 6 $ show score) ++ " / LEFT : " ++ show left
  where
    setw n s = (replicate (n - length s) '0') ++ s

render shape (x, y) = renderPrimitive Polygon $ mapM_ vertex $ map makeVertex3 shape
  where
    makeVertex3 (dx, dy) = Vertex3 (x + dx) (y + dy) (0.0::GLfloat)

-- event handlers

display env = do
  draw env

reshape env (Size w h) = do
  modifyIORef env update
  viewport $= (Position 0 0, Size w h)
  loadIdentity
  ortho (-0.5) ((convd w) - 0.5) ((convd h) - 0.5) (-0.5) (-1.0) (1.0)
    where
      update (win, ship, sbs, as, abs, score, left) =
        ((0, 0, convf w, convf h), ship, sbs, as, abs, score, left)

keyboardMouse env key keystate modifiers position = do
  case key of
    SpecialKey KeyLeft  -> modifyIORef env $ moveShip ToLeft
    SpecialKey KeyRight -> modifyIORef env $ moveShip ToRight
    SpecialKey KeyUp    -> modifyIORef env $ moveShip ToUp
    SpecialKey KeyDown  -> modifyIORef env $ moveShip ToDown
    Char ' '            -> do
      (_, _, sbs, _, _, _, _) <- readIORef env
      if length sbs == 0
        then modifyIORef env (\ (w, sp, sbs, as, abs, s, l) -> (w, sp, (shipPos sp):sbs, as, abs, s, l))
        else return ()
    Char 'q'            -> throwIO $ ExitException ExitSuccess
    _                   -> return ()

timer env = do
  f <- randomRIO (0::Int, 19)
  seed <- newStdGen
  fs <- return $ randomRs (0::Int, 19) seed
  modifyIORef env $ updateEnv f fs
  draw env
  (_, ship, _, _, _, _, left) <- readIORef env
  if hit ship
    then do
      modifyIORef env (\ (win, ship, sbs, as, abs, score, left) -> (win, Ship (shipPos ship) False, sbs, as, abs, score, left))
      if left < 0
        then return ()
        else addTimerCallback (interval * 10) $ timer env
    else addTimerCallback interval $ timer env

main = do
  env <- newIORef initialEnv
  getArgsAndInitialize
  initialDisplayMode    $= [RGBAMode, DoubleBuffered]
  initialWindowPosition $= Position 100 100
  initialWindowSize     $= Size windowWidth windowHeight
  createWindow "to write more comprehensible code"
  displayCallback       $= display env
  reshapeCallback       $= Just (reshape env)
  keyboardMouseCallback $= Just (keyboardMouse env)
  addTimerCallback interval $ timer env
  mainLoop
